#ifndef COMPRESSION_HPP
#define COMPRESSION_HPP

#include <string>
#include "huffman_node.hpp"
#include "bit_io.hpp"
#include "huffman_core.hpp"

void writeTree(Node *root, BitWriter &writer);
void compress(const std::string &inputFilename, const std::string &outputFilename);

#endif