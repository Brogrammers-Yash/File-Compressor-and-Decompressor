#include <iostream>
#include <unordered_map>
#include <queue>
#include <functional>
#include <sstream>
#include <bitset>
#include "../Node/Node.h"
#include "../FrequencyCounter/FrequencyCounter.h"

using namespace std;

#ifndef HUFFMAN_CODE_H
#define HUFFMAN_CODE_H

class HuffmanCode {
    unordered_map<char, string> char_code;
    Node* huffmanTreeRoot;

    class customComparator {
        public:
        bool operator() (Node*, Node*);
    };

    void buildEncodingTree(unordered_map<char, int>);
    void encodeCharacters(Node*, string);
    int saveCompressedFile(string);
    void writeHeader(ofstream&);
    void writeData(ifstream&, ofstream&);
    void readHeader(ifstream&);
    void buildDecodingTree();
    string readData(ifstream&);
    int getTotalCharacters(ifstream&);
    int saveDecompressedFile(string, int, string);
    int getFileSize(string);
    int getEncodedDataSize(unordered_map<char, int>);

public:
    pair<int, int> compress(string);
    pair<int, int> decompress(string);
};

#endif