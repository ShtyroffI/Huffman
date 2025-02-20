#include "huffman_node.hpp"

Node::Node(char symbol, int freq)
    : symbol(symbol), freq(freq), left(nullptr), right(nullptr) {}


Node::Node(int freq, Node *left, Node *right)
    : symbol('\0'), freq(freq), left(left), right(right) {}
