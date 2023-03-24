//
// Created by adrie on 24/03/2023.
//

#include "SFMLLoader.hpp"

SFMLLoader::SFMLLoader() {
    this->_pathCell.loadFromFile("Sprites/sand_tile.png");
    this->_notWalkableCell.loadFromFile("Sprites/grass_tile_2.png");
 //   this->_wallCell.loadFromFile();
   // this->_mapBorder.loadFromFile();
}

SFMLLoader::~SFMLLoader() {

}