#include "HuffmanCode/HuffmanCode.h"

int main(int argc, char** argv) {
    string command, file_name;
    HuffmanCode huffmanCode;

    if(argc != 3) {
        cout << "Invalid command!" << endl;
        return 0;
    }

    command = argv[1];
    file_name = argv[2];

    if(command == "compress") {

        auto file_size = huffmanCode.compress(file_name);

        if(!file_size.second) {
            cout << "cannot compress file" << endl;
        } else {
            cout << "original file size : " << file_size.first << " bytes" << endl;
            cout << "compressed file size : " << file_size.second << " bytes" << endl;
            cout << "file compressed by " << (1 - (double) file_size.second / file_size.first) * 100 << " %" <<endl;
        }

    } else if(command == "decompress") {

        auto file_size = huffmanCode.decompress(file_name);

        cout << "compressed file size : " << file_size.first << " bytes" << endl;
        cout << "decompressed file size : " << file_size.second << " bytes" << endl;

    } else {
        cout << "Invalid command!" << endl;
    }

    return 0;
}