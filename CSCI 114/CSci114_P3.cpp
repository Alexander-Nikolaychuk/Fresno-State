#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <thread>

using namespace std;

/*

----- INSTRUCTIONS TO RUN -----

	This program runs as is according to the assignment. Once
compiled, it takes three arguments, each an int. In order, they are M, N, K, which are 
used to build all three matrices. It reads from two files named "A.txt" and "B.txt". It then prints out
the C matrix.

Command to compile: "g++ CSci114_P3.cpp -o P3.exe -pthread"
Format to run: "./P3 1 1 1" 

*/

void calculateCRow(const vector<vector<int>>& A,
                 const vector<vector<int>>& B,
                 vector<vector<int>>& C,
                 int M, int N, int K,
                 int startRow, int endRow) {
	int store = 0;
	int row = 0;
	int column = 0;
	
	for(int i = startRow; i < endRow; i++) {
		for(int j = 0; j < K; j++) {
			store = 0;
			row = 0;
		    column = 0;
			
			for(int k = 0; k < N; k++) {
				store = store + (A[i][column++] * B[row++][j]);
			}
			
			C[i][j] = store;
		}
	}
}

int main(int argc, char* argv[]) {
	
	// Make sure the number of arguments is correct. 
	if(argc != 4){
		std::cerr << "Not enough arguments, or too many. Please provide three. Read Directions to run program.\n";
		return 1;
	}
		
    int M = std::stoi(argv[1]);  //Initalize Arguments to Ints
    int N = std::stoi(argv[2]);
	int K = std::stoi(argv[3]);
	
	vector<vector<int>> A(M, vector<int>(N));  //Initalize 2D arrays for matrixes using the Int arguments
	vector<vector<int>> B(N, vector<int>(K));
	vector<vector<int>> C(M, vector<int>(K));
	
	ifstream Afile("A.txt");  //Open files to fill matrix A and B
	ifstream Bfile("B.txt");

    //Check if the files opened
    if (!Afile || !Bfile) {
        std::cerr << "Failed to open A.txt or B.txt\n";
        return 1;
    }
	
	string line;  //This is the string that will be used to grab one line from the file, 
	              // then the << can work on it without going to next line in the file.
	istringstream rowStream(line);  //However, '<<' works on streams, not strings, so we need this converter. 
	
	for(int i = 0; i < M; i++) {
		if (!getline(Afile, line)) { // If line does not exist, then there is not enough rows.
            cerr << "A.txt: Not enough rows in file.\n";
            return 1;
        }
		
		rowStream.clear();    //Neccesary to reuse isstringstream
		rowStream.str(line);
		
		for(int j = 0; j < N; j++) {
			if (!(rowStream >> A[i][j])) { //Check if there is enough numbers in a row for << to read
				cerr << "A.txt: Not enough numbers in row " << i << ", expected " << N << "\n";
				return 1;
			}
		}	
		
	}
	
	// Read B in a similar way. 

	rowStream.clear();
    rowStream.str(line);

	for(int i = 0; i < N; i++) {
		if (!getline(Bfile, line)) {
            cerr << "B.txt: Not enough rows in file\n";
            return 1;
        }
		
		rowStream.clear();
		rowStream.str(line);
		
		for(int j = 0; j < K; j++) {
			if (!(rowStream >> B[i][j])) {
				cerr << "B: Not enough numbers in row " << i << ", expected " << K << "\n";
				return 1;
			}
		}	
		
	}
	
	// Ready for main task: Computing C
	
	unsigned int threadCount = thread::hardware_concurrency();
    if (threadCount == 0) {
        threadCount = 4;
    }

    if (threadCount > static_cast<unsigned int>(M)) {
        threadCount = M;
    }

    vector<thread> threads;
    int rowsPerThread = M / threadCount;
    int extraRows = M % threadCount;

    int startRow = 0;
    for (unsigned int t = 0; t < threadCount; t++) {
        int endRow = startRow + rowsPerThread + (t < static_cast<unsigned int>(extraRows) ? 1 : 0);

        threads.emplace_back(calculateCRow,
                             cref(A), cref(B), ref(C),
                             M, N, K,
                             startRow, endRow);

        startRow = endRow;
    }

    for (auto& th : threads) {
        th.join();
    }
	
	// Print out the C matrix
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < K; j++) {
			cout << C[i][j] << " ";
		}
		cout << "\n";
	}

    return 0;
}