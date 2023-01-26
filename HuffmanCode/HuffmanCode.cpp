#include "HuffmanCode.h"

#define SEPARATOR char(32)

bool HuffmanCode::customComparator::operator() (Node* node1, Node* node2) {
    return node1->getFrequency() > node2->getFrequency();
}

void HuffmanCode::buildEncodingTree(unordered_map<char, int> frequency_map) {
    priority_queue<Node*, vector<Node*>, customComparator> huffman_queue;

    for(auto &character : frequency_map) {
        huffman_queue.push(new Node(character.first, character.second));
    }

    if(huffman_queue.size() == 1) {
        Node* node = huffman_queue.top();
        huffman_queue.pop();

        Node* newNode = new Node(128, node->getFrequency());
        newNode->setLeft(node);

        huffman_queue.push(newNode);
    }

    while(huffman_queue.size() > 1) {
        Node* leftNode = huffman_queue.top();
        huffman_queue.pop();
        Node* rightNode = huffman_queue.top();
        huffman_queue.pop();

        Node* newNode = new Node(128, leftNode->getFrequency() + rightNode->getFrequency());
        newNode->setLeft(leftNode);
        newNode->setRight(rightNode);

        huffman_queue.push(newNode);
    }

    function<void(Node*)> printTree = [&] (Node* node) {
        if(node == nullptr) return;

        printTree(node->getLeft());
        // cout<<node->getCharacter()<<" "<<node->getFrequency()<<endl;
        printTree(node->getRight());
    };

    printTree(huffman_queue.top());
    huffmanTreeRoot = huffman_queue.top();
}

int HuffmanCode::getEncodedDataSize(unordered_map<char, int> char_frequency) {
    int size = 0;

    for(auto character : char_frequency) {
        size += character.second * char_code[character.first].size();
    }

    return size;
}

void HuffmanCode::encodeCharacters(Node* node, string code) {
    if(node == nullptr) return;

    if(node->getLeft() == nullptr && node->getRight() == nullptr) {
        char_code[node->getCharacter()] = code;
    }

    encodeCharacters(node->getLeft(), code + '0');
    encodeCharacters(node->getRight(), code + '1');
}

void HuffmanCode::writeHeader(ofstream& output_file) {
    output_file << char_code.size() << " ";
    for(const auto& character : char_code) {
        output_file << character.first << " " << character.second << " ";
    }
}

void HuffmanCode::writeData(ifstream& input_file, ofstream& output_file) {
    string compressedData;
    char ch;
    int total_characters = 0;

    while(input_file.get(ch)) {
        compressedData += char_code[ch];
        total_characters++;
    }

    input_file.close();

    while(compressedData.size() % 8 != 0) {
        compressedData += '0';
    }

    stringstream stringStream(compressedData);

    output_file << total_characters << " ";

    while(stringStream.good()) {
        bitset<8> bits;
        stringStream >> bits;
        output_file << char(bits.to_ulong());
        // cout<<ch;
    }

    output_file.close();
}

int HuffmanCode::saveCompressedFile(string file_name) {
    ifstream input_file;
    ofstream output_file;

    input_file.open(file_name, ios::binary);
    output_file.open(file_name + ".apzip", ios::binary);

    writeHeader(output_file);
    writeData(input_file, output_file);

    int compressed_file_size = getFileSize(file_name + ".apzip");
    return compressed_file_size;
}

pair<int, int> HuffmanCode::compress(string inputFile) {
    FrequencyCounter frequencyCounter;
    frequencyCounter.countFrequency(inputFile);

    int original_file_size = getFileSize(inputFile);
    auto char_frequency = frequencyCounter.getFrequencyMap();

    buildEncodingTree(char_frequency);

    encodeCharacters(huffmanTreeRoot, "");

    int encodedSize = getEncodedDataSize(char_frequency);
    
    if(encodedSize > 0.8 * original_file_size * 8) {
        return {original_file_size, 0};
    }

    // cout<<endl<<"character codes:"<<endl;
    // for(auto ch : char_code) {
    //     cout<<ch.first<<"\t"<<(int)ch.first<<"\t"<<ch.second<<endl;
    // }

    int compressed_file_size = saveCompressedFile(inputFile);

    return {original_file_size, compressed_file_size};
}

void HuffmanCode::readHeader(ifstream& compressed_file) {
    char ch, character;
    string str;
    int header_size;

    compressed_file.get(ch);
    while(ch != SEPARATOR) {
        str += ch;
        compressed_file.get(ch);
    }

    header_size = stoi(str);
    // cout<<header_size<<endl;

    for(int i=0; i<header_size; i++) {
        str = "";
        compressed_file.get(character);

        compressed_file.get(ch);
        compressed_file.get(ch);
        
        while(ch != SEPARATOR) {
            str += ch;
            compressed_file.get(ch);
        }

        char_code[character] = str;
        // cout<<character<<"\t"<<str<<endl;
    }
}

int HuffmanCode::getTotalCharacters(ifstream& compressed_file) {
    char ch;
    string total_characters;

    compressed_file.get(ch);
    while(ch != SEPARATOR) {
        total_characters += ch;
        compressed_file.get(ch);
    }

    return stoi(total_characters);
}

string HuffmanCode::readData(ifstream& compressed_file) {
    char ch;
    string data;

    while(compressed_file.get(ch)) {
        bitset<8> bits(ch);
        data += bits.to_string();
    }

    return data;
}

void HuffmanCode::buildDecodingTree() {
    huffmanTreeRoot = new Node(128, 0);
    Node* currentNode;

    for(const auto& character : char_code) {
        string code = character.second;
        Node* newNode = new Node(character.first, 0);
        currentNode = huffmanTreeRoot;

        for(int i=0; i<code.length(); i++) {
            if(code[i] == '0') {
                if(i == code.length() - 1) {
                    currentNode->setLeft(newNode);
                } else if(currentNode->getLeft() == nullptr) {
                    currentNode->setLeft(new Node(128, 0));
                }
                currentNode = currentNode->getLeft();
            } else {
                if(i == code.length() - 1) {
                    currentNode->setRight(newNode);
                } else if(currentNode->getRight() == nullptr) {
                    currentNode->setRight(new Node(128, 0));
                }
                currentNode = currentNode->getRight();
            }
        }
    }

    function<void(Node*)> printTree = [&] (Node* node) {
        if(node == nullptr) return;

        printTree(node->getLeft());
        // cout<<node->getCharacter()<<" "<<node->getFrequency()<<endl;
        printTree(node->getRight());
    };

    printTree(huffmanTreeRoot);
}

int HuffmanCode::saveDecompressedFile(string data, int total_characters, string file_name) {
    ofstream output_file;
    output_file.open(file_name, ios::binary);
    Node* currentNode = huffmanTreeRoot;
    int current_characters = 0;

    for(int i=0; i<data.length(); i++) {
        if(data[i] == '0') {
            currentNode = currentNode->getLeft();
        } else {
            currentNode = currentNode->getRight();
        }

        if(currentNode->getLeft() == nullptr && currentNode->getRight() == nullptr) {
            output_file << currentNode->getCharacter();
            currentNode = huffmanTreeRoot;
            current_characters++;

            if(current_characters == total_characters) break;
        }
    }

    output_file.close();

    int decompressed_file_size = getFileSize(file_name);
    return decompressed_file_size;
}

pair<int, int> HuffmanCode::decompress(string file_name) {
    char_code.clear();

    ifstream compressed_file;
    compressed_file.open(file_name, ios::binary);

    readHeader(compressed_file);

    buildDecodingTree();

    int total_characters = getTotalCharacters(compressed_file);

    string data = readData(compressed_file);

    // cout<<data<<endl;

    int decompressed_file_size = saveDecompressedFile(data, total_characters, file_name.substr(0, file_name.length() - 6));
    int original_file_size = getFileSize(file_name);

    return {original_file_size, decompressed_file_size};
}

int HuffmanCode::getFileSize(string file_name) {
    ifstream file_stream(file_name, ios::binary);
    file_stream.seekg(0, ios::end);
    return file_stream.tellg();
}