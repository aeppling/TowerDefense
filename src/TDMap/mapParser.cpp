//
// Created by adrie on 06/02/2023.
//

#include "mapParser.hpp"
#include <string>

mapParser::mapParser(std::string filePath, TDMap *map) {
    std::string     line;

    this->_filePath = filePath;
    std::ifstream file(this->_filePath);
    if (file.is_open()) {
        while (getline(file, line)) {
            map->constructAddLine(doubleCharOnString(line));
            map->constructAddLine(doubleCharOnString(line));
            map->constructAddLine(doubleCharOnString(line));
            doubleCharOnString(line);
        }
    }
    else {
        std::cout << "Unable to open file";
    }
    file.close();
}

mapParser::~mapParser() {}

std::string mapParser::doubleCharOnString(std::string inputString) {
    int         i = 0;
    int         y = 0;
    std::string result(inputString.size() * 3, 'E');

    while (y < inputString.size()) {
        result[i++] = inputString[y];
        result[i++] = inputString[y];
        result[i++] = inputString[y++];
    }
    return (result);
}
