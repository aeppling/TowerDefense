//
// Created by adrie on 06/02/2023.
//

#ifndef UNTITLED1_TDMAP_HPP
#define UNTITLED1_MAP_HPP

#include <iostream>
#include <fstream>
#include <string>

#include "TDMap.hpp"


class   mapParser {
private:
    std::string     _filePath;
public:
    mapParser(std::string filePath, TDMap *map);
    ~mapParser();
    std::string doubleCharOnString(std::string inputString);
};

#endif