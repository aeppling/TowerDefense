//
// Created by adrie on 06/02/2023.
//
#include "mapParser.hpp"
#include "TDMap.hpp"
#include "SizeRatioCalculator.hpp"

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
    int cellSize = getCellSize(winSizeX, winSizeY, this->_map.at(0).size(), this->_map.size());
    int y = 0;
    while (y != this->_map.size()) {
        int x = 0;
        std::vector<sf::Sprite> newSpriteLine;
        while (x != this->_map.at(y).size()) {
            sf::Sprite newSprite;
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
            newSpriteLine.push_back(newSprite);
            x++;
        }
        this->_tilesSprites.push_back(newSpriteLine);
        y++;
    }
}

void TDMap::refreshTextures(SFMLLoader &sfmlLoader) {
    int y = 0;
    while (y != this->_map.size()) {
        int x = 0;
        while (x != this->_map.at(y).size()) {
            switch (this->_map.at(y).at(x).getType()) {
                case 'X':
                    this->_tilesSprites.at(y).at(x).setTexture(sfmlLoader.getPathCell());
                    this->_tilesSprites.at(y).at(x).setColor(sf::Color::Green);
                    break;
                case 'W':
                    this->_tilesSprites.at(y).at(x).setTexture(sfmlLoader.getWallCell());
                    this->_tilesSprites.at(y).at(x).setColor(sf::Color::Red);
                    break;
                case 'S':
                    this->_tilesSprites.at(y).at(x).setTexture(sfmlLoader.getPathCell());
                    this->_tilesSprites.at(y).at(x).setColor(sf::Color::Yellow);
                    break;
                case 'B':
                    this->_tilesSprites.at(y).at(x).setTexture(sfmlLoader.getPathCell());
                    this->_tilesSprites.at(y).at(x).setColor(sf::Color::Blue);
                    break;
                case 'A':
                    this->_tilesSprites.at(y).at(x).setTexture(sfmlLoader.getPathCell());
                    this->_tilesSprites.at(y).at(x).setColor(sf::Color::Blue);
                    break;
            }
            x++;
        }
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