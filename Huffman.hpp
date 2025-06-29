#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char c, int f);
};

struct Compare {
    bool operator()(Node* a, Node* b);
};

class HuffmanCoding {
public:
    HuffmanCoding();
    ~HuffmanCoding();

    void compress(const string& inputFile, const string& outputFile);
    void decompress(const string& compressedFile, const string& outputFile);
private:
    unordered_map<char, string> huffmanCodes;
    unordered_map<char, int> frequencies;
    Node* root;

    void buildFrequencyMap(const string& filename);
    void buildHuffmanTree();
    void generateCodes(Node* node, const string& code);
    void encodeAndWrite(const string& inputFile, const string& outputFile);
    void clear(Node* node);
};

#endif
