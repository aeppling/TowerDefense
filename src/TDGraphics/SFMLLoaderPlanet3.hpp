//
// Created by adrie on 10/05/2023.
//

#ifndef UNTITLED1_SFMLLOADERPLANET3_HPP
#define UNTITLED1_SFMLLOADERPLANET3_HPP

#include "SFMLLoader.hpp"

class SFMLLoaderPlanet3 : public SFMLLoader {
public:
    SFMLLoaderPlanet3() : SFMLLoader("Sprites/MyTiles/tileSpawnCell.png", "Sprites/MyTiles/SpawnCellHeight.png",
                                     "Sprites/MyTiles/tileGoo_slope.png", "Sprites/MyTiles/tileGoo.png") {};
};

#endif //UNTITLED1_SFMLLOADERPLANET3_HPP
