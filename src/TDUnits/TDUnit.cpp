//
// Created by adrie on 17/03/2023.
//

#include <iostream>
#include <math.h>
#include "TDUnit.hpp"
#include "../TDGame/SizeRatioCalculator.hpp"
#include "../TDGraphics/SFMLLoader.hpp"

TDUnit::TDUnit(int hp, int speed, int resistance, int posX, int posY, bool isFlying, int value, SFMLLoader &sfmlLoaderUnit) {
    this->_health_points = hp;
    this->_speed = speed;
    this->_resistance = resistance;
    this->_posX = posX;
    this->_posY = posY;
    this->_isFlying = isFlying;
    this->_value = value;
    this->_timeOfLastMove = std::chrono::steady_clock::now();
    this->_alreadyCount = false;
    this->_alreadyArrived = false;
}

void    TDUnit::live() {
    while (!(this->isAtBase()) && this->isAlive() == true) {
        std::chrono::steady_clock::time_point testTime = std::chrono::steady_clock::now();
        int res = std::chrono::duration_cast<std::chrono::milliseconds>(testTime - this->_timeOfLastMove).count();
        if (res >= this->_speed) {
            if (!(this->isAtBase())) {
               // std::cout << "Move now " << '[' + this->getTypeName() + "] :" << " Current pos x:" << this->_posX << " y:" << this->_posY
                //          << std::endl;
                this->move();
                this->_timeOfLastMove = std::chrono::steady_clock::now();
            }
        }
    }
}

void    TDUnit::run(TDMap *map) {
    //UNCOMMENT TO DEBUG PATH
    this->_mapCopy = map;
    this->_thread = std::thread(&TDUnit::live, this);
}

void    TDUnit::move() {
    std::shared_ptr<MapCell> nextTo = this->_path[0];
    if ((isBlocked(nextTo->getPosX(), nextTo->getPosY())) && (this->_isFlying == false)) {
        this->_path.clear();
        this->searchPath(this->_mapCopy->getMapVector(), this->_baseCoordX, this->_baseCoordY);
        this->move();
       //nextTo = this->_path[0];
    }
    else {
        this->rotate(this->_posX, this->_posY, nextTo->getPosX(), nextTo->getPosY());
        if ((this->_posX != nextTo->getPosX()) && (this->_posY != nextTo->getPosY()))
            std::cout << "Took diagonal" << std::endl;

        std::chrono::steady_clock::time_point totalTime = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point elapsedAll = std::chrono::steady_clock::now();

        int res = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedAll - totalTime).count();
        std::chrono::steady_clock::time_point markerTime = std::chrono::steady_clock::now();
        while (res < this->_speed) {
            std::chrono::steady_clock::time_point elapsed = std::chrono::steady_clock::now();
            int resInter = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed - markerTime).count();
            if (resInter > this->_spriteSpeed) {
                //NEED FOR EACH DIRECTION
                markerTime = std::chrono::steady_clock::now();
                this->rotate(this->_posX, this->_posY, nextTo->getPosX(), nextTo->getPosY());
            }
            elapsedAll = std::chrono::steady_clock::now();
            res = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedAll - totalTime).count();
        }

        this->_posX = nextTo->getPosX();
        this->_posY = nextTo->getPosY();
        //  this->_sprite.move(;)
        this->_path.erase(this->_path.begin());
    }
}

//benjamin.labastille@

void    TDUnit::searchPath(std::vector<std::vector<MapCell>> *nmap, int baseCoordX, int baseCoordY) {
    this->_baseCoordX = baseCoordX;
    this->_baseCoordY = baseCoordY;
    AStarPathFinding pathFinder((*nmap), (*nmap)[this->_posY][this->_posX], (*nmap)[baseCoordY][baseCoordX]);
    pathFinder.runPathFinding(this->_path, this->_isFlying);
}

void    TDUnit::setSprite(SFMLEnemiesLoader &sfmlLoader, int winSizeX, int winSizeY, int mapSizeX, int mapSizeY, int cellSize) {
    // GET SIZE RATIO OF UNITS SPRITE FROM WINDOW AND MAP
    //SFML RELOAD & SFMLLOADUNIT CLASS FOR RESSOURCES

    this->_spriteSpeed = (cellSize / this->_speed);
    this->_unitSize = getCellSize(winSizeX, winSizeY, mapSizeX, mapSizeY);
    this->_cellSize = cellSize;
    if (this->getTypeName() == "Missile")
        this->_sprite.setTexture(*sfmlLoader.getMissile());
    else if (this->getTypeName() == "Drone")
        this->_sprite.setTexture(*sfmlLoader.getDrone());
    else if (this->getTypeName() == "Alien")
        this->_sprite.setTexture(*sfmlLoader.getAlien());
    else if (this->getTypeName() == "Spaceship")
        this->_sprite.setTexture(*sfmlLoader.getSpaceship());
    float scaleFactor = static_cast<float>(cellSize) / static_cast<float>(this->_sprite.getTexture()->getSize().x);
    sf::IntRect textureRect(0, 0, this->_sprite.getTexture()->getSize().x, this->_sprite.getTexture()->getSize().y);
    this->_sprite.setScale(scaleFactor, scaleFactor);
    if (this->getTypeName() == "Spaceship")
        this->_sprite.setScale(scaleFactor*2.5, scaleFactor*2.5);
    if (this->getTypeName() == "Alien")
        this->_sprite.setScale(scaleFactor*1.5, scaleFactor*1.5);
    // this->_sprite.setColor(sf::Color::Blue);
    this->_sprite.setTextureRect(textureRect);
    sf::Vector2f newOrigin(this->_sprite.getLocalBounds().width / 2.f, this->_sprite.getLocalBounds().height / 2.f);
    this->_sprite.setOrigin(newOrigin);
    this->_sprite.setPosition((this->_posX * this->_unitSize) + cellSize/2, (this->_posY * this->_unitSize) + cellSize / 2);
/*    this->_unitSize = getCellSize(winSizeX, winSizeY, mapSizeX, mapSizeY);
    sf::Sprite newSprite;
    newSprite.setTexture(*sfmlLoader.getCowards());
    newSprite.setColor(sf::Color::White);
    sf::IntRect textureRect(0, 0, this->_unitSize - 3, this->_unitSize - 3); // -3 to see border and debug
    newSprite.setTextureRect(textureRect);
    newSprite.setPosition(this->_posX * this->_unitSize, this->_posY * this->_unitSize);
    this->_sprite = newSprite;*/
}

bool    TDUnit::isAtBase() {
    if (this->_path.size() > 0) {
        return (false);
    }
    else {
        return (true);
    }
}

bool    TDUnit::isBlocked(int nextPosX, int nextPosY) {
    if (this->_mapCopy->getElem(nextPosX, nextPosY)->isWalkable() == false)
        return (true);
    else
        return (false);
}

bool    TDUnit::isAlive() {
    if (this->_health_points <= 0)
        return (false);
    else
        return (true);
}

void    TDUnit::getShot(int damage) {
    this->_sprite.setColor(sf::Color::Red);
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    this->_sprite.setColor(sf::Color::White);
    this->_health_points = this->_health_points - damage;
}

void    TDUnit::getKill() {
    this->_sprite.setColor(sf::Color::Red);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    this->_sprite.setColor(sf::Color::White);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    this->_sprite.setColor(sf::Color::Red);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    this->_sprite.setColor(sf::Color::White);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    this->_sprite.setColor(sf::Color::Red);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    this->_sprite.setColor(sf::Color::Transparent);
    this->_thread.join();
//    delete this;
}

void    TDUnit::rotate(float posX, float posY, float destX, float destY) {
    float dx = destX - posX;
    float dy = destY - posY;

    float rotationAngle = atan2(dy, dx) * 180 / 3.14159f;
    this->_sprite.setRotation(rotationAngle + 90);

    if (dx > 0) {
        this->_sprite.setTextureRect(sf::IntRect(0, 0, this->_sprite.getTexture()->getSize().x, this->_sprite.getTexture()->getSize().y));
    } else {
        this->_sprite.setTextureRect(sf::IntRect(this->_sprite.getTexture()->getSize().x, 0, -this->_sprite.getTexture()->getSize().x, this->_sprite.getTexture()->getSize().y));
    }
    this->_sprite.setPosition((this->_posX * this->_unitSize) + this->_cellSize/2, (this->_posY * this->_unitSize) + this->_cellSize / 2);
}