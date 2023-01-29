#include "FrequencyCounter.h"

void FrequencyCounter::countFrequency(string file_name) {
    char ch;
    ifstream input_file;
    int tot_ch = 0;

    input_file.open(file_name, ios::binary);

    while(input_file.get(ch)) {
        frequency_map[ch]++;
    }

    input_file.close();
}

const unordered_map<char, int>& FrequencyCounter::getFrequencyMap() const {
    return frequency_map;
}