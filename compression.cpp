#include "compression.hpp"
#include <fstream>
#include <cstdint>
#include <iostream>
#include <map>

static uint64_t getFileSize(const std::string &filename)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    uint64_t size = file.tellg();
    file.close();
    return size;
}

void writeTree(Node *root, BitWriter &writer)
{
    if (!root->left && !root->right)
    {
        writer.writeBit(1);
        writer.writeByte(root->symbol);
    }
    else
    {
        writer.writeBit(0);
        writeTree(root->left, writer);
        writeTree(root->right, writer);
    }
}

void compress(const std::string &inputFilename, const std::string &outputFilename)
{
    auto freqMap = buildFrequencyTable(inputFilename);
    if (freqMap.empty())
    {
        std::cerr << "File is empty!" << std::endl;
        return;
    }

    Node *root = buildHuffmanTree(freqMap);
    std::map<char, std::string> codes;
    generateCodes(root, "", codes);

    std::ofstream outputFile(outputFilename, std::ios::binary);
    BitWriter writer(outputFile);

    uint64_t fileSize = getFileSize(inputFilename);
    outputFile.write(reinterpret_cast<const char *>(&fileSize), sizeof(fileSize));

    writeTree(root, writer);

    std::ifstream inputFile(inputFilename, std::ios::binary);
    char c;
    while (inputFile.get(c))
    {
        std::string code = codes[static_cast<unsigned char>(c)];
        for (char bit : code)
        {
            writer.writeBit(bit - '0');
        }
    }

    writer.flush();
    inputFile.close();
    outputFile.close();
    deleteTree(root);
}