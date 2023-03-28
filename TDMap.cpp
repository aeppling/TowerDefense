//
// Created by adrie on 06/02/2023.
//
#include "mapParser.hpp"
#include "TDMap.hpp"

TDMap::TDMap(std::string filename, SFMLLoader sfmlLoader, int winSizeX, int winSizeY) {
    this->_constructIterator = 0;
    new mapParser(filename, this);
    this->setAllPositions();
    this->setAllTextures(sfmlLoader, winSizeX, winSizeY);
}

TDMap::~TDMap() {

}

#define CELL_SIZE 20
#define TILE_SIZE 20
void TDMap::setAllTextures(SFMLLoader sfmlLoader, int winSizeX, int winSizeY) {
    int smallerWinSize = std::min(winSizeX, winSizeY);
    int largerMapSize = std::max(this->_map.size(), this->_map[0].size());
    int cellSize = std::min(smallerWinSize / largerMapSize, smallerWinSize / largerMapSize);

    if ((this->_map.size() > 30) || (this->_map[0].size() > 30))
        cellSize = cellSize / 1.1;
    if ((this->_map.size() > 40) || (this->_map[0].size() > 40))
        cellSize = cellSize / 1.2;
    if ((this->_map.size() > 60) || (this->_map[0].size() > 60))
        cellSize = cellSize / 1.3;
    int y = 0;
    while (y != this->_map.size()) {
        int x = 0;
        while (x != this->_map.at(y).size()) {
            sf::Sprite newSprite;
            std::cout << this->_map.at(y).at(x).getType();
            if (this->_map.at(y).at(x).getType() == 'S') {
                newSprite.setTexture(sfmlLoader.getPathCell());
                newSprite.setColor(sf::Color::Yellow);
            }
            else if (this->_map.at(y).at(x).getType() == 'B') {
                newSprite.setTexture(sfmlLoader.getPathCell());
                newSprite.setColor(sf::Color::Blue);
            }
            else if (this->_map.at(y).at(x).isWalkable()) {
                newSprite.setTexture(sfmlLoader.getPathCell());
                newSprite.setColor(sf::Color::Green);
            }
            else {
                newSprite.setTexture(sfmlLoader.getNotWalkableCell());
                newSprite.setColor(sf::Color::Red);
            }
            sf::IntRect textureRect(0, 0, cellSize - 3, cellSize - 3); // -3 to see border and debug
            newSprite.setTextureRect(textureRect);
            newSprite.setPosition(this->_map.at(y).at(x).getPosX() * cellSize, this->_map.at(y).at(x).getPosY() * cellSize);
            this->_tilesSprites.push_back(newSprite);
            x++;
        }
        std::cout << std::endl;
        y++;
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