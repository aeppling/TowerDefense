//
// Created by adrie on 24/03/2023.
//

#ifndef UNTITLED1_SFMLLOADER_HPP
#define UNTITLED1_SFMLLOADER_HPP

#include "SFML/Graphics.hpp"
#include <memory>

class SFMLLoader {
private:
    sf::Texture _pathCell;
    sf::Texture _notWalkableCell;
    sf::Texture _wallCell;
    sf::Texture _spawnCell;
    sf::Texture _baseCell;
    sf::Texture _towerBasic;
    sf::Texture _mapBorder;
    sf::Texture _cowards;
    sf::Texture _bats;
    sf::Texture _golem;
public:
    SFMLLoader();
    ~SFMLLoader();
    // GETTERS
    sf::Texture *getPathCell() { return (&this->_pathCell); }
    sf::Texture *getWallCell() { return (&this->_wallCell); }
    sf::Texture *getNotWalkableCell() { return (&this->_notWalkableCell); }
    sf::Texture *getSpawnCell() { return (&this->_spawnCell); }
    sf::Texture *getBaseCell() { return (&this->_baseCell); }
    sf::Texture *getTowerBasic() { return (&this->_towerBasic); }
    sf::Texture getMapBorder() { return (this->_mapBorder); }
    sf::Texture getCowards() { return (this->_cowards); }
    sf::Texture getBats() { return (this->_bats); }
    sf::Texture getGolem() { return (this->_golem); }
};

#endif //UNTITLED1_SFMLLOADER_HPP
