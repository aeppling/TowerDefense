//
// Created by adrie on 06/02/2023.
//
#include "mapParser.hpp"
#include "TDMap.hpp"

TDMap::TDMap(std::string filename) {
    this->_constructIterator = 0;
    new mapParser(filename, this);
    this->setAllPositions();
    //this->setAllTextures();
}

TDMap::~TDMap() {

}

void TDMap::setAllTextures() {
    std::vector<sf::Sprite> sprites;
    int i = 0;
    while (i != this->_map.size()) {
        sf::Sprite sprite();
/*        sprite.setPosition(cell.x * CELL_SIZE, cell.y * CELL_SIZE);
        this->_tilesSprites.push_back(sprite);
        i++;*/
    }
}

void TDMap::constructAddLine(std::string lineToAdd) {
    int i = 0;
    std::vector<MapCell> newLine;

    while (i < lineToAdd.length()) {
        MapCell newCell(lineToAdd[i], i, this->_constructIterator);
        newLine.push_back(newCell);
        i++;
    }
    this->_map.push_back(newLine);
    this->_constructIterator++;
}

void TDMap::setAllPositions() {
    int x = 0;
    int y = 0;

    while (y != this->_map.size()) {
        x = 0;
        while (x != this->_map[y].size()) {
            this->_map[y][x].setPosX(x);
            this->_map[y][x].setPosY(y);
            x++;
        }
        y++;
    }
}

void TDMap::displayAsciiMap() {
    int x;
    int y = 0;

    while (y < this->_map.size()) {
        x = 0;
        while (x < this->_map[y].size()) {
            std::cout << "coord x&y :" << this->_map[y][x].getPosX() << " : " << this->_map[y][x].getPosY() << std::endl;
//            std::cout << this->_map[y][x];
            x++;
        }
        std::cout << std::endl;
        y++;
    }
    std::cout << "END OF DEBUG DISPLAY" << std::endl << std::endl;
}