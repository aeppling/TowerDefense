//
// Created by adrie on 24/03/2023.
//

#include <iostream>

#include "SFMLLoader.hpp"

SFMLLoader::SFMLLoader(std::string pathCell, std::string pathCellHeights, std::string wallCell, std::string wallCellHeights) {
    // MAP CELL THAT WILL CHANGE
    if (!(this->_pathCell.loadFromFile(pathCell)))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_pathCellHeight.loadFromFile(pathCellHeights)))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_notWalkableCell.loadFromFile(wallCell)))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_notWalkableCellHeight.loadFromFile(wallCellHeights)))
        std::cout << "Error on loading texture..." << std::endl;
    // THAT WILL NOT MOVE
    if (!(this->_wallCell.loadFromFile("ressources/Sprites/MyTiles/IndustrialTileSet1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_spawnCell.loadFromFile("ressources/Sprites/MyTiles/tileSpawnCell.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_spawnBuilding.loadFromFile("ressources/Sprites/MyTiles/spawnBuilding.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_baseCell.loadFromFile("ressources/Sprites/MyTiles/tileStone_slope.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_baseBuilding.loadFromFile("ressources/Sprites/MyTiles/scifiStructure_07.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_towerBasic.loadFromFile("ressources/Sprites/MyTiles/turret_1_1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_towerSupport.loadFromFile("ressources/Sprites/MyTiles/body_tracks.png")))
        std::cout << "Error on loading texture..." << std::endl;

    //this->_pathCell.setSmooth(false);
    //this->_notWalkableCell.setSmooth(false);
    //   this->_wallCell.loadFromFile();
   // this->_mapBorder.loadFromFile();
}

SFMLLoader::~SFMLLoader() {

}