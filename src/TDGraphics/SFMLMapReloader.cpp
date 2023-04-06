//
// Created by adrie on 06/04/2023.
//

#include <iostream>
#include "SFMLMapReloader.hpp"

SFMLMapReloader::SFMLMapReloader() {
    if (!(this->_pathCell.loadFromFile("Sprites/sand_tile.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_wallCell.loadFromFile("Sprites/MyTiles/IndustrialTileSet1.png")))
        std::cout << "Error on loading texture..." << std::endl;
}
