//
// Created by adrie on 24/03/2023.
//

#include <iostream>

#include "SFMLLoader.hpp"

SFMLLoader::SFMLLoader() {
    if (!(this->_pathCell.loadFromFile("Sprites/sand_tile.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_notWalkableCell.loadFromFile("Sprites/tile_0001.png")))
        std::cout << "Error on loading texture..." << std::endl;
    std::cout << "texture size X: " << this->_pathCell.getSize().x << " : "<< this->_pathCell.getSize().y << std::endl;
    std::cout << "texture size T: " << this->_notWalkableCell.getSize().x << " : "<< this->_notWalkableCell.getSize().y << std::endl;
    //this->_pathCell.setSmooth(false);
    //this->_notWalkableCell.setSmooth(false);
    //   this->_wallCell.loadFromFile();
   // this->_mapBorder.loadFromFile();
}

SFMLLoader::~SFMLLoader() {

}