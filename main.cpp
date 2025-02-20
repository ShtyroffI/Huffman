#include <iostream>
#include "compression.hpp"
#include "decompression.hpp"

int main()
{
    std::string mode, inputFile, outputFile;
    std::cout << "Enter mode (compress/decompress): ";
    std::cin >> mode;
    std::cout << "Enter input filename: ";
    std::cin >> inputFile;
    std::cout << "Enter output filename: ";
    std::cin >> outputFile;

    if (mode == "compress")
    {
        compress(inputFile, outputFile);
    }
    else if (mode == "decompress")
    {
        decompress(inputFile, outputFile);
    }
    else
    {
        std::cerr << "Invalid mode!" << std::endl;
    }

    return 0;
}