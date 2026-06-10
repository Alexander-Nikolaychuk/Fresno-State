/*
=============Instructions to run in cygwin =============

**************this cpp should can only run in cygwin, visual studio, etc doesn't recognize fork() as a function

Assuming you have put the file : CSci114_P2 into your folder containing cygwin

Steps:

1.  Open CSci114_P1.cpp and edit line with inFile.open, only "H.docx" part to the type and name of the file
    we will be using save and exit once the change has been done.

2. Run Cygwin then type "g++ CSci114_P1.cpp" without quatation marks, and a space between g++ and CSci.

3. after the second step, we execute the program by doing this: ./a.exe
    a.exe is the excution, but we need ./ before it.

4. After running ./a.exe, and typing ls, we will see a  "data.out" file
    type in the terminal : mv data.out sample.docx
    after that  visit your folder containing the new file, we should be able to open the file.
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int A_to_B[2];

static ssize_t write_all(int fd, const void* buf, size_t n) {  //Helper functions to write n bytes
    const char* p = (const char*)buf;
    size_t total = 0;
    while (total < n) {
        ssize_t w = write(fd, p + total, n - total);
        if (w < 0) {
            if (errno == EINTR) continue;
            return -1;
        }
        total += (size_t)w;
    }
    return (ssize_t)total;
}

static ssize_t read_all(int fd, void* buf, size_t n) {  //Helper functions to read n bytes
    char* p = (char*)buf;
    size_t total = 0;
    while (total < n) {
        ssize_t r = read(fd, p + total, n - total);
        if (r < 0) {
            if (errno == EINTR) continue;
            return -1;
        }
        if (r == 0) break; //pipe closed (EOF)
        total += (size_t)r;
    }
    return (ssize_t)total;
}

int main() {
    int status = 0;

    if (pipe(A_to_B) == -1) {  //Make sure pipe started up 
        perror("pipe");
        return 1;
    }

    pid_t pidA = fork();  //Create fork
    if (pidA < 0) {
        perror("fork A");
        return 1;
    }

                                 //Process A
    if (pidA == 0) {
        close(A_to_B[0]);  //A writes

        int inFd = open("data.in", O_RDONLY);
        if (inFd < 0) {
            perror("open data.in");
            close(A_to_B[1]);
            _exit(1);
        }

        off_t sz = lseek(inFd, 0, SEEK_END);  //Get file size
        if (sz < 0) {
            perror("lseek end");
            close(inFd);
            close(A_to_B[1]);
            _exit(1);
        }
        if (lseek(inFd, 0, SEEK_SET) < 0) {
            perror("lseek set");
            close(inFd);
            close(A_to_B[1]);
            _exit(1);
        }

        uint64_t file_size = (uint64_t)sz;

        if (write_all(A_to_B[1], &file_size, sizeof(file_size)) < 0) {  //Send header: file size
            perror("write file_size");
            close(inFd);
            close(A_to_B[1]);
            _exit(1);
        }

        const size_t BUF_SZ = 64 * 1024;  //Send file data in chunks
        char buffer[BUF_SZ];

        uint64_t sent = 0;
        while (sent < file_size) {
            ssize_t r = read(inFd, buffer, BUF_SZ);
            if (r < 0) {
                if (errno == EINTR) continue;
                perror("read data.in");
                close(inFd);
                close(A_to_B[1]);
                _exit(1);
            }
            if (r == 0) break; //unexpected EOF

            if (write_all(A_to_B[1], buffer, (size_t)r) < 0) {
                perror("write pipe");
                close(inFd);
                close(A_to_B[1]);
                _exit(1);
            }
            sent += (uint64_t)r;
        }

        const char term[4] = {'e','o','f','\0'};  //Termination message after file content (as required)
        if (write_all(A_to_B[1], term, sizeof(term)) < 0) {
            perror("write term");
            close(inFd);
            close(A_to_B[1]);
            _exit(1);
        }

        close(inFd);
        close(A_to_B[1]);  //also causes EOF on pipe
        _exit(0);
    }

    pid_t pidB = fork();
    if (pidB < 0) {
        perror("fork B");
        return 1;
    }

                                     //Process B
    if (pidB == 0) {
        close(A_to_B[1]);  //B only reads

        int outFd = open("data.out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outFd < 0) {
            perror("open data.out");
            close(A_to_B[0]);
            _exit(1);
        }

        //Read header: file size
        uint64_t file_size = 0;
        ssize_t got = read_all(A_to_B[0], &file_size, sizeof(file_size));
        if (got != (ssize_t)sizeof(file_size)) {
            fprintf(stderr, "Failed to read file size header.\n");
            close(outFd);
            close(A_to_B[0]);
            _exit(1);
        }

        //Read exactly file_size bytes and write to output
        const size_t BUF_SZ = 64 * 1024;
        char buffer[BUF_SZ];

        uint64_t received = 0;
        while (received < file_size) {
            uint64_t remaining = file_size - received;
            size_t want = (remaining < BUF_SZ) ? (size_t)remaining : BUF_SZ;

            ssize_t r = read(A_to_B[0], buffer, want);
            if (r < 0) {
                if (errno == EINTR) continue;
                perror("read pipe");
                close(outFd);
                close(A_to_B[0]);
                _exit(1);
            }
            if (r == 0) {
                fprintf(stderr, "Pipe closed early.\n");
                close(outFd);
                close(A_to_B[0]);
                _exit(1);
            }

            if (write_all(outFd, buffer, (size_t)r) < 0) {
                perror("write data.out");
                close(outFd);
                close(A_to_B[0]);
                _exit(1);
            }

            received += (uint64_t)r;
        }

        //Read termination message ("eof\0") after file bytes
        char term[4] = {0,0,0,0};
        got = read_all(A_to_B[0], term, sizeof(term));
        //If A closed the pipe quickly, got might be 0; but we *attempted* to read it.
        if (got == (ssize_t)sizeof(term) && strcmp(term, "eof") != 0) {
            fprintf(stderr, "Warning: termination message mismatch: '%s'\n", term);
        }

        close(outFd);
        close(A_to_B[0]);
        _exit(0);
    }

                          //Parent
    close(A_to_B[0]);
    close(A_to_B[1]);

    waitpid(pidA, &status, 0);
    waitpid(pidB, &status, 0);

    printf("Finished\n");
    return 0;
}