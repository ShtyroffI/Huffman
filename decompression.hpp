#ifndef DECOMPRESSION_HPP
#define DECOMPRESSION_HPP

#include <string>
#include "huffman_node.hpp"
#include "bit_io.hpp"
#include "huffman_core.hpp"

Node *readTree(BitReader &reader);
void decompress(const std::string &inputFilename, const std::string &outputFilename);

#endif