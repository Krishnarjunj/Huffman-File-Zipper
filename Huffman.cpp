#include "Huffman.hpp"

Node::Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}

bool Compare::operator()(Node* a, Node* b) {
    return a->freq > b->freq;
}

HuffmanCoding::HuffmanCoding() : root(nullptr) {}

HuffmanCoding::~HuffmanCoding() {
    clear(root);
}

void HuffmanCoding::buildFrequencyMap(const string& filename) {
    ifstream in(filename, ios::binary);
    char ch;
    while (in.get(ch)) {
        frequencies[ch]++;
    }
    in.close();
}

void HuffmanCoding::buildHuffmanTree() {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& pair : frequencies) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    root = pq.top();
}

void HuffmanCoding::generateCodes(Node* node, const string& code) {
    if (!node) return;
    if (!node->left && !node->right) {
        huffmanCodes[node->ch] = code;
    }
    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

void HuffmanCoding::encodeAndWrite(const string& inputFile, const string& outputFile) {
    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);
    string encoded;

    char ch;
    while (in.get(ch)) {
        encoded += huffmanCodes[ch];
    }
    in.close();

    out << (int)huffmanCodes.size() << '\n';
    for (auto& p : huffmanCodes) {
        out << p.first << ' ' << p.second << '\n';
    }

    for (size_t i = 0; i < encoded.size(); i += 8) {
        string byte = encoded.substr(i, 8);
        while (byte.length() < 8) byte += '0';
        bitset<8> b(byte);
        out.put(static_cast<char>(b.to_ulong()));
    }
    out.close();
}

void HuffmanCoding::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void HuffmanCoding::compress(const string& inputFile, const string& outputFile) {
    buildFrequencyMap(inputFile);
    buildHuffmanTree();
    generateCodes(root, "");
    encodeAndWrite(inputFile, outputFile);
}

void HuffmanCoding::decompress(const string& compressedFile, const string& outputFile) {
    ifstream in(compressedFile, ios::binary);
    ofstream out(outputFile, ios::binary);

    int mapSize;
    in >> mapSize;
    in.get(); // skip newline

    unordered_map<string, char> reverseCodes;
    for (int i = 0; i < mapSize; i++) {
        char ch;
        string code;
        in.get(ch);
        in.get(); // space
        getline(in, code);
        reverseCodes[code] = ch;
    }

    string bitstream;
    char byte;
    while (in.get(byte)) {
        bitset<8> bits(static_cast<unsigned char>(byte));
        bitstream += bits.to_string();
    }
    in.close();

    string temp = "";
    for (char bit : bitstream) {
        temp += bit;
        if (reverseCodes.find(temp) != reverseCodes.end()) {
            out.put(reverseCodes[temp]);
            temp = "";
        }
    }

    out.close();
}
