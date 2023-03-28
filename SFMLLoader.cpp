//
// Created by adrie on 24/03/2023.
//

#include <iostream>

#include "SFMLLoader.hpp"

SFMLLoader::SFMLLoader() {
    if (!(this->_pathCell.loadFromFile("Sprites/sand_tile.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_notWalkableCell.loadFromFile("Sprites/grass_tile_2.png")))
        std::cout << "Error on loading texture..." << std::endl;
    //this->_pathCell.setSmooth(false);
    //this->_notWalkableCell.setSmooth(false);
    //   this->_wallCell.loadFromFile();
   // this->_mapBorder.loadFromFile();
}

SFMLLoader::~SFMLLoader() {

}