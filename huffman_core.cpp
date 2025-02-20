#include "huffman_core.hpp"
#include <fstream>
#include <queue>
#include <vector>

std::map<char, int> buildFrequencyTable(const std::string &filename)
{
    std::ifstream file(filename, std::ios::binary);
    std::map<char, int> freqMap;
    char c;
    while (file.get(c))
    {
        freqMap[static_cast<unsigned char>(c)]++;
    }
    file.close();
    return freqMap;
}

Node *buildHuffmanTree(const std::map<char, int> &freqMap)
{
    struct Compare
    {
        bool operator()(Node *l, Node *r) { return l->freq > r->freq; }
    };

    std::priority_queue<Node *, std::vector<Node *>, Compare> minHeap;
    for (auto &pair : freqMap)
    {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() > 1)
    {
        Node *left = minHeap.top();
        minHeap.pop();
        Node *right = minHeap.top();
        minHeap.pop();
        minHeap.push(new Node(left->freq + right->freq, left, right));
    }

    return minHeap.empty() ? nullptr : minHeap.top();
}

void generateCodes(Node *root, std::string code, std::map<char, std::string> &codes)
{
    if (!root)
        return;
    if (!root->left && !root->right)
    {
        codes[root->symbol] = code;
        return;
    }
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

void deleteTree(Node *root)
{
    if (!root)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
