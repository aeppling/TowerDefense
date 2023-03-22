//
// Created by adrie on 20/03/2023.
//

#ifndef UNTITLED1_RETRIEVELEVEL_HPP
#define UNTITLED1_RETRIEVELEVEL_HPP

#include <vector>
#include <string>
#include "TDUnit.hpp"

class RetrieveLevel {
private:
    int _actual_level = 1;
public:
    RetrieveLevel();
    RetrieveLevel(int starting_level);
    ~RetrieveLevel();

    std::vector<std::vector<TDUnit*>> getNextLevel();
    std::vector<TDUnit*> getWaveFromString(std::string waveString);
};

#endif //UNTITLED1_RETRIEVELEVEL_HPP
