//
// Created by adrie on 04/05/2023.
//

#include "SFMLDecorationLoader.hpp"

#include <iostream>

SFMLDecorationLoader::SFMLDecorationLoader() {
    if (!(this->_rock1.loadFromFile("Sprites/MyTiles/rock1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_bush2.loadFromFile("Sprites/MyTiles/foliageBush_small.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_tree1.loadFromFile("Sprites/MyTiles/foliageTree_green.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_alienBush.loadFromFile("Sprites/MyTiles/scifiEnvironment_16.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_alienTree1.loadFromFile("Sprites/MyTiles/scifiEnvironment_13.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_alienTree2.loadFromFile("Sprites/MyTiles/scifiEnvironment_14.png")))
        std::cout << "Error on loading texture..." << std::endl;
}

SFMLDecorationLoader::~SFMLDecorationLoader() {

}