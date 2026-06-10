#include <fstream>
#include <iostream>
#include <vector>

int main() {
    std::ifstream in("data.in", std::ios::binary);

    //check if the IN file opened properly
    if (!in) {
        std::cerr << "Failed to open data.in\n";
        return 1;
    }

    //check if the OUT file opened properly
    std::ofstream out("data.out", std::ios::binary | std::ios::trunc);
    if (!out) {
        std::cerr << "Failed to open data.out\n";
        return 1;
    }


    //Initalize buffer
    const std::size_t BUF_SIZE = 1 << 20; // 1MB buffer
    std::vector<char> buffer(BUF_SIZE);

    //While the file is open, read for size of buffer. Then create object 'n' to make sure that 
    // we have more than nothing to copy. Then copy.
    while (in) {
        in.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
        std::streamsize n = in.gcount();
        if (n > 0) out.write(buffer.data(), n);
    }


    //Make sure the outfile was still open at this point 
    if (!out) {
        std::cerr << "Write error\n";
        return 1;
    }

    return 0;
}