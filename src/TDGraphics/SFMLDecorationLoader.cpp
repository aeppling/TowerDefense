//
// Created by adrie on 04/05/2023.
//

#include "SFMLDecorationLoader.hpp"

#include <iostream>

SFMLDecorationLoader::SFMLDecorationLoader() {
    if (!(this->_rock1.loadFromFile("ressources/Sprites/MyTiles/rock1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_bush2.loadFromFile("ressources/Sprites/MyTiles/foliageBush_small.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_tree1.loadFromFile("ressources/Sprites/MyTiles/foliageTree_green.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_alienBush.loadFromFile("ressources/Sprites/MyTiles/scifiEnvironment_16.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_alienTree1.loadFromFile("ressources/Sprites/MyTiles/scifiEnvironment_13.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_alienTree2.loadFromFile("ressources/Sprites/MyTiles/scifiEnvironment_14.png")))
        std::cout << "Error on loading texture..." << std::endl;
}

SFMLDecorationLoader::~SFMLDecorationLoader() {

}