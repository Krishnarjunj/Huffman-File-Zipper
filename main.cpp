#include "Huffman.hpp"

using namespace std;

int main() {
    HuffmanCoding huff;

    cout << "Choose mode:\n1. Compress\n2. Decompress\n> ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        string input = "input.txt";
        string output = "compressed.huff";
        huff.compress(input, output);
        cout << "Compression done. File: " << output << endl;
    } else if (choice == 2) {
        string input = "compressed.huff";
        string output = "output.txt";
        huff.decompress(input, output);
        cout << "Decompression done. File: " << output << endl;
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
