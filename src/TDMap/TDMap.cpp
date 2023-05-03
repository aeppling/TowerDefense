//
// Created by adrie on 06/02/2023.
//
#include "mapParser.hpp"
#include "TDMap.hpp"
#include "../TDGame/SizeRatioCalculator.hpp"

sf::Texture text;
sf::Sprite spr;

TDMap::TDMap(std::string filename, SFMLLoader &sfmlLoader, int winSizeX, int winSizeY, std::shared_ptr<SpritesHolder> &spriteHolder) : _sfmlLoader(sfmlLoader), _spritesHolderPtr(spriteHolder) {
    this->_constructIterator = 0;
    new mapParser(filename, this);
    this->setAllPositions();
    this->setAllTextures(sfmlLoader, winSizeX, winSizeY, this->_spritesHolderPtr);
    //SET SPRITE HOLDER AFTER SETALLPOSITION
    // ASSIGN EACH POSITION AND SPRITE ON SPRITE HOLDER AND THEN LOAD TEXTURE
    // EAACH REFRESH RELOAD TEXTURE IF NECESSARY
}

TDMap::~TDMap() {

}

#define CELL_SIZE 20
#define TILE_SIZE 20
void TDMap::setAllTextures(SFMLLoader &sfmlLoader, int winSizeX, int winSizeY, std::shared_ptr<SpritesHolder> spriteHolder) {
    this->_cellSize = getCellSize(winSizeX, winSizeY, this->_map.at(0).size(), this->_map.size());
    int y = 0;

    while (y != this->_map.size()) {
        int x = 0;
        while (x != this->_map.at(y).size()) {
            spriteHolder->setSpriteFromTypeAndPosition(&this->_map.at(y).at(x), this, sfmlLoader, this->_cellSize);
            x++;
        }
        y++;
    }
}

void TDMap::refreshTextures(int posX, int posY) {
    std::cout << "Refresh." << std::endl;
    if (this->_spritesHolderPtr->getSpriteFromPosition(posX, posY) == nullptr) {
        std::cout << "Not FOund."<< std::endl;
        return ;
    }
    else if (this->_map.at(posY).at(posX).getType() != this->_spritesHolderPtr->getSpriteFromPosition(posX, posY)->getType()) {
            this->_spritesHolderPtr->updateSpriteFromTypeAndPosition(
                    this->_spritesHolderPtr->getSpriteFromPosition(posX, posY)->getType(),
                    posX, posY, this->_sfmlLoader, this->_cellSize, this->_map.at(posY).at(posX).getType());
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
    int x;
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