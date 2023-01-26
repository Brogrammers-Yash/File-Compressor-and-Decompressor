#include <iostream>
#include <unordered_map>
#include <fstream>

using namespace std;

#ifndef FREQUENCY_COUNTER_H
#define FREQUENCY_COUNTER_H

class FrequencyCounter {
    unordered_map<char, int> frequency_map;

    public:
        const unordered_map<char, int>& getFrequencyMap() const;
        void countFrequency(string file_name);
};

#endif