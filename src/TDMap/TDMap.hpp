//
// Created by adrie on 06/02/2023.
//

#ifndef UNTITLED1_TDMAP_HPP
#define UNTITLED1_TDMAP_HPP

#include <vector>
#include "../TDGraphics/SFMLLoader.hpp"
#include "MapCell.hpp"
#include "../TDGraphics/SpritesHolder.hpp"

class SpritesHolder;

class TDMap {
private:
    std::vector<std::vector<MapCell>>                _map;
    int                                              _constructIterator;
    std::vector<std::vector<sf::Sprite>>             _tilesSprites;
public:
    // (DE)CONSTRUCTOR AND OVERLOADS
    TDMap(std::string filename, SFMLLoader &sfmlLoader, int winSizeX, int winSizeY, std::shared_ptr<SpritesHolder> spriteHolder);
    ~TDMap();

    // MAP CONSTRUCTION
    void constructAddLine(std::string lineToAdd);
    void displayAsciiMap();

    // GETTER & SETTER
    sf::Sprite                          getTileSprite(int countY, int countX) { return (this->_tilesSprites.at(countY).at(countX)); }
    int                                 getTileMaxSpriteY() { return(this->_tilesSprites.size()); }
    int                                 getTileMaxSpriteX(int countY) { return(this->_tilesSprites.at(countY).size()); }
    std::vector<std::vector<MapCell>>   *getMapVector() { return(&this->_map); };
    int                                 getSizeY() { return(this->_map.size()); };
    int                                 getSizeX() { return(this->_map[0].size()); };
    MapCell                             *getElem(int x, int y) { return (&this->_map[y][x]); }

    // INITIALISE
    void setAllPositions();
    void setAllTextures(SFMLLoader &sfmlLoader, int winSizeX, int winSizeY, std::shared_ptr<SpritesHolder> spriteHolder);

    // OTHERS FUNCTION
    void refreshTextures(SFMLLoader &sfmlLoader, std::shared_ptr<SpritesHolder> spritesHolderPtr, int cellSize, int posX, int posY);
};

#endif //UNTITLED1_TDMAP_HPP
