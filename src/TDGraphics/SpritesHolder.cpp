//
// Created by adrie on 05/04/2023.
//

#include <iostream>
#include "SpritesHolder.hpp"

void        SpritesHolder::setSpriteFromTypeAndPosition(MapCell *mapCell, TDMap *map,
                                                        SFMLLoader &sfmlLoader, int cellSize) {
    SFMLSprite sprite;
    std::shared_ptr<SFMLSprite> newSprite = std::make_shared<SFMLSprite>(sprite);
    if (mapCell->getType() == 'X') {
        newSprite->setSpriteCutted(sfmlLoader.getPathCell(), cellSize, mapCell->getPosX(), mapCell->getPosY(), mapCell->getType(), 1);
        newSprite->setPosition(cellSize);
        this->_walkableSprite.push_back(newSprite);
    }
    else if (mapCell->getType() == 'T') {
        if (mapCell->getPosY() + 1 >= map->getSizeY())
            newSprite->setSpriteCutted(sfmlLoader.getNotWalkableCellHeight(), cellSize, mapCell->getPosX(), mapCell->getPosY(), mapCell->getType(), 1);
        else if (map->getElem(mapCell->getPosX(), mapCell->getPosY() + 1)->getType() != 'T')
            newSprite->setSpriteCutted(sfmlLoader.getNotWalkableCellHeight(), cellSize, mapCell->getPosX(), mapCell->getPosY(), mapCell->getType(), 1);
        else
            newSprite->setSpriteCutted(sfmlLoader.getNotWalkableCell(), cellSize, mapCell->getPosX(), mapCell->getPosY(), mapCell->getType(), 1);
        newSprite->setPosition(cellSize);
        this->_notWalkableSprite.push_back(newSprite);
    }
    else if (mapCell->getType() == 'W') {
        newSprite->setSprite(sfmlLoader.getWallCell(), cellSize, mapCell->getPosX(), mapCell->getPosY(), mapCell->getType(), 1);
        newSprite->setPosition(cellSize);
        this->_wallSprite.push_back(newSprite);
    }
    else if (mapCell->getType() == 'B') {
        if ((mapCell->getPosX() + 1 < map->getSizeX()) && (mapCell->getPosX() - 1 > 0) &&
                (mapCell->getPosY() - 1 > 0) && (mapCell->getPosY() + 1 < map->getSizeY())) {
            if ((map->getElem(mapCell->getPosX(), mapCell->getPosY() + 1)->getType() == 'B') &&
                (map->getElem(mapCell->getPosX(), mapCell->getPosY() - 1)->getType() == 'B')
                && (map->getElem(mapCell->getPosX() + 1, mapCell->getPosY())->getType() == 'B') &&
                (map->getElem(mapCell->getPosX() - 1, mapCell->getPosY())->getType() == 'B'))
                newSprite->setSpriteCutted(sfmlLoader.getBaseBuilding(), cellSize, mapCell->getPosX(), mapCell->getPosY(),
                                     mapCell->getType(), 1);
            else
                newSprite->setSpriteCutted(sfmlLoader.getBaseCell(), cellSize, mapCell->getPosX(), mapCell->getPosY(), mapCell->getType(), 1);
        }
        else
            newSprite->setSpriteCutted(sfmlLoader.getBaseCell(), cellSize, mapCell->getPosX(), mapCell->getPosY(), mapCell->getType(), 1);
        newSprite->setPosition(cellSize);
        this->_baseSprite.push_back(newSprite);
    }
    else if (mapCell->getType() == 'S') {
        if ((mapCell->getPosX() + 1 < map->getSizeX()) && (mapCell->getPosX() - 1 > 0) &&
            (mapCell->getPosY() - 1 > 0) && (mapCell->getPosY() + 1 < map->getSizeY())) {
            if ((map->getElem(mapCell->getPosX(), mapCell->getPosY() + 1)->getType() == 'S') &&
                (map->getElem(mapCell->getPosX(), mapCell->getPosY() - 1)->getType() == 'S')
                && (map->getElem(mapCell->getPosX() + 1, mapCell->getPosY())->getType() == 'S') &&
                (map->getElem(mapCell->getPosX() - 1, mapCell->getPosY())->getType() == 'S'))
                newSprite->setSpriteCutted(sfmlLoader.getSpawnCell(), cellSize, mapCell->getPosX(), mapCell->getPosY(),
                                           mapCell->getType(), 1);
            else
                newSprite->setSpriteCutted(sfmlLoader.getSpawnCell(), cellSize, mapCell->getPosX(), mapCell->getPosY(), mapCell->getType(), 1);
        }
        else
            newSprite->setSpriteCutted(sfmlLoader.getSpawnCell(), cellSize, mapCell->getPosX(), mapCell->getPosY(), mapCell->getType(), 1);
        newSprite->setPosition(cellSize);
        this->_spawnSprite.push_back(newSprite);
    }
}

void       SpritesHolder::updateSpriteFromTypeAndPosition(char type, int posX, int posY,
                                                          SFMLLoader &sfmlLoader, int cellSize, char newType) {
    if (type == 'X') {
        int i = 0;
        while (i != this->_walkableSprite.size()) {
            if ((this->_walkableSprite.at(i)->getPosX()) == posX && (this->_walkableSprite.at(i)->getPosY() == posY)) {
                    this->_walkableSprite.at(i)->setSprite(sfmlLoader.getWallCell(), cellSize, posX, posY, newType, 1);
                    auto it = this->_walkableSprite.begin() + i;
                    std::shared_ptr<SFMLSprite> removed_element = *it;
                    this->_walkableSprite.erase(it);
                    this->_wallSprite.insert(this->_wallSprite.begin(), removed_element);
                    this->_wallSprite.at(0)->getSprite().setColor(sf::Color::Black);
                return;
            }
            i++;
        }
    }
    else if (type == 'T') {
        int i = 0;
        while (i != this->_notWalkableSprite.size()) {
            if ((this->_notWalkableSprite.at(i)->getPosX()) == posX && (this->_notWalkableSprite.at(i)->getPosY() == posY)) {
                this->_notWalkableSprite.at(i)->setSpriteCutted(sfmlLoader.getNotWalkableCell(), cellSize, posX, posY, newType, 1);
                return;
            }
            i++;
        }
    }
    else if (type == 'W') {
        int i = 0;
        while (i != this->_wallSprite.size()) {
            if ((this->_wallSprite.at(i)->getPosX()) == posX && (this->_wallSprite.at(i)->getPosY() == posY)) {
                this->_wallSprite.at(i)->setSprite(sfmlLoader.getPathCell(), cellSize, posX, posY, newType, 1);
                auto it = this->_wallSprite.begin() + i;
                std::shared_ptr<SFMLSprite> removed_element = *it;
                this->_wallSprite.erase(it);
                this->_walkableSprite.insert(this->_walkableSprite.begin(), removed_element);
                this->_walkableSprite.at(0)->getSprite().setColor(sf::Color::Green);
                return;
            }
            i++;
        }
    }
}

std::shared_ptr<SFMLSprite>     SpritesHolder::getSpriteFromPosition(int posX, int posY) {
    int i = 0;
    while (i != this->_walkableSprite.size()) {
        if ((this->_walkableSprite.at(i)->getPosX() == posX)
        && (this->_walkableSprite.at(i)->getPosY() == posY)) {
            return (this->_walkableSprite.at(i));
        }
        i++;
    }
    i = 0;
    while (i != this->_notWalkableSprite.size()) {
        if ((this->_notWalkableSprite.at(i)->getPosX() == posX)
            && (this->_notWalkableSprite.at(i)->getPosY() == posY)) {
            return (this->_notWalkableSprite.at(i));
        }
        i++;
    }

    i = 0;
    while (i != this->_wallSprite.size()) {
        if ((this->_wallSprite.at(i)->getPosX() == posX)
            && (this->_wallSprite.at(i)->getPosY() == posY)) {
            return (this->_wallSprite.at(i));
        }
        i++;
    }
    std::cout << "No Sprite found in refresh (update)..." << std::endl;
    std::cout << "posX: " << posX << " posY : "<< posY<< std::endl;
    return (nullptr);
}

void                            SpritesHolder::displayMap(sf::RenderWindow &window, int cellSize, SFMLLoader &sfmlLoaderMap) {
    int i = 0;
    while (i != this->_walkableSprite.size()) {
        this->_walkableSprite.at(i)->setPosition(cellSize);
        window.draw(this->_walkableSprite.at(i)->getSprite());
        i++;
    }
    i = 0;
    while (i != this->_notWalkableSprite.size()) {
        this->_notWalkableSprite.at(i)->setPosition(cellSize);
        window.draw(this->_notWalkableSprite.at(i)->getSprite());
        i++;
    }
    i = 0;
    while (i != this->_wallSprite.size()) {
        this->_wallSprite.at(i)->setPosition(cellSize);
//        this->_wallSprite.at(i)->getSprite().setTexture(*sfmlLoaderTest.getWallCell());
        window.draw(this->_wallSprite.at(i)->getSprite());
        i++;
    }
    i = 0;
    while (i != this->_baseSprite.size()) {
        this->_baseSprite.at(i)->setPosition(cellSize);
        window.draw(this->_baseSprite.at(i)->getSprite());
        i++;
    }
    i = 0;
    while (i != this->_spawnSprite.size()) {
        this->_spawnSprite.at(i)->setPosition(cellSize);
        window.draw(this->_spawnSprite.at(i)->getSprite());
        i++;
    }
}

void                            SpritesHolder::displayDebug() {
   int i = 0;
   std::cout << "Path cells : " << std::endl;
   while (i != this->_walkableSprite.size()) {
       std::cout << "pos x:" << this->_walkableSprite.at(i)->getSprite().getPosition().x;
       std::cout << " y:" << this->_walkableSprite.at(i)->getSprite().getPosition().y;
       i++;
   }
   i = 0;
    std::cout << "Not Walkable cells : " << std::endl;
    while (i != this->_notWalkableSprite.size()) {
        std::cout << "pos x:" << this->_notWalkableSprite.at(i)->getSprite().getPosition().x;
        std::cout << " y:" << this->_notWalkableSprite.at(i)->getSprite().getPosition().y;
        i++;
    }
    i = 0;
    std::cout << "Wall cells : " << std::endl;
    while (i != this->_wallSprite.size()) {
        std::cout << "pos x:" << this->_wallSprite.at(i)->getSprite().getPosition().x;
        std::cout << " y:" << this->_wallSprite.at(i)->getSprite().getPosition().y;
        i++;
    }
}