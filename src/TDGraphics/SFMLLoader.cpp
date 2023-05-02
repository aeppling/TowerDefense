//
// Created by adrie on 24/03/2023.
//

#include <iostream>

#include "SFMLLoader.hpp"

SFMLLoader::SFMLLoader() {
    if (!(this->_pathCell.loadFromFile("Sprites/MyTiles/tileSand_slope.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_pathCellHeight.loadFromFile("Sprites/MyTiles/tileSand.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_notWalkableCell.loadFromFile("Sprites/MyTiles/tileGrass_slope.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_notWalkableCellHeight.loadFromFile("Sprites/MyTiles/tileGrass.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_wallCell.loadFromFile("Sprites/MyTiles/IndustrialTileSet1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_spawnCell.loadFromFile("Sprites/MyTiles/tileGoo_slope.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_spawnBuilding.loadFromFile("Sprites/MyTiles/tileGoo_slope.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_baseCell.loadFromFile("Sprites/MyTiles/tileStone_slope.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_baseBuilding.loadFromFile("Sprites/MyTiles/scifiStructure_07.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_towerBasic.loadFromFile("Sprites/MyTiles/turret_1_1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_towerSupport.loadFromFile("Sprites/MyTiles/body_tracks.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_cowards.loadFromFile("Sprites/Units/CharRed1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    //this->_pathCell.setSmooth(false);
    //this->_notWalkableCell.setSmooth(false);
    //   this->_wallCell.loadFromFile();
   // this->_mapBorder.loadFromFile();
}

SFMLLoader::~SFMLLoader() {

}