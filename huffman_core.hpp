#ifndef HUFFMAN_CORE_HPP
#define HUFFMAN_CORE_HPP

#include <map>
#include <string>
#include "huffman_node.hpp"

void deleteTree(Node *root);
void generateCodes(Node *root, std::string code, std::map<char, std::string> &codes);

std::map<char, int> buildFrequencyTable(const std::string &filename);
Node *buildHuffmanTree(const std::map<char, int> &freqMap);
void generateCodes(Node *root, std::string code, std::map<char, std::string> &codes);
void deleteTree(Node *root);

#endif
