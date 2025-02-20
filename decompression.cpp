#include "decompression.hpp"
#include <fstream>
#include <cstdint>
#include <iostream>

Node *readTree(BitReader &reader)
{
    int bit = reader.readBit();
    if (bit == 1)
    {
        char symbol = reader.readByte();
        return new Node(symbol, 0);
    }
    else if (bit == 0)
    {
        Node *left = readTree(reader);
        Node *right = readTree(reader);
        return new Node(0, left, right);
    }
    return nullptr;
}

void decompress(const std::string &inputFilename, const std::string &outputFilename)
{
    std::ifstream inputFile(inputFilename, std::ios::binary);
    BitReader reader(inputFile);

    uint64_t fileSize;
    inputFile.read(reinterpret_cast<char *>(&fileSize), sizeof(fileSize));

    Node *root = readTree(reader);
    if (!root)
    {
        std::cerr << "Invalid tree!" << std::endl;
        return;
    }

    std::ofstream outputFile(outputFilename, std::ios::binary);
    Node *current = root;
    uint64_t decodedBytes = 0;

    if (!root->left && !root->right)
    {
        for (uint64_t i = 0; i < fileSize; i++)
        {
            outputFile.put(root->symbol);
        }
    }
    else
    {
        while (decodedBytes < fileSize)
        {
            int bit = reader.readBit();
            if (bit == -1)
                break;

            current = (bit == 0) ? current->left : current->right;

            if (!current->left && !current->right)
            {
                outputFile.put(current->symbol);
                current = root;
                decodedBytes++;
            }
        }
    }

    outputFile.close();
    inputFile.close();
    deleteTree(root);
}