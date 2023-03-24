//
// Created by adrie on 06/02/2023.
//

#ifndef UNTITLED1_TDMAP_HPP
#define UNTITLED1_TDMAP_HPP

#include <vector>
#include "SFMLLoader.hpp"
#include "MapCell.hpp"

class TDMap {
private:
    std::vector<std::vector<MapCell>>   _map;
    int                                 _constructIterator;
    std::vector<sf::Sprite>             _tilesSprites;
public:
    // (DE)CONSTRUCTOR AND OVERLOADS
    TDMap(std::string filename);
    ~TDMap();

    // MAP CONSTRUCTION
    void constructAddLine(std::string lineToAdd);
    void displayAsciiMap();

    // GETTER & SETTER
    std::vector<std::vector<MapCell>>   *getMapVector() { return(&this->_map); };
    int                                 getSizeY() { return(this->_map.size()); };
    int                                 getSizeX() { return(this->_map[0].size()); };

    // INITIALISE
    void setAllPositions();
    void setAllTextures();
};

#endif //UNTITLED1_TDMAP_HPP
