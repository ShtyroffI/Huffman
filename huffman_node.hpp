#ifndef HUFFMAN_NODE_HPP
#define HUFFMAN_NODE_HPP

#include <cstdint>

struct Node
{
    char symbol;
    int freq;
    Node *left;
    Node *right;

    Node(char symbol, int freq);
    Node(int freq, Node *left, Node *right);
};

#endif
