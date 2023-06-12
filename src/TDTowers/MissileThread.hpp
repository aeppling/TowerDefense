//
// Created by adrie on 12/04/2023.
//

#ifndef UNTITLED1_MISSILETHEEAD_HPP
#define UNTITLED1_MISSILETHEEAD_HPP

#include "../TDGraphics/SFMLMissileLoader.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

class MissileThread {
private:
    bool        _isArrived;
    sf::Sprite  _sprite;
    std::thread _thread;
    std::string _style;
    sf::Sprite  _explosionSprite;
public:
    MissileThread();
    ~MissileThread() {};
    void animateExplosion();
    void initStyle(SFMLMissileLoader &sfmlMissileLoader);
    void startThread(SFMLMissileLoader &sfmlMissileLoader, const sf::Vector2f& startPosition, const sf::Vector2f& endPosition,
                     int cellSize, float speed, std::string style);

    void shootMissile(SFMLMissileLoader &sfmlMissileLoader,
                      const sf::Vector2f& startPosition, const sf::Vector2f& endPosition, int &cellSize, float &speed);
    sf::Sprite getSprite();
    sf::Sprite getExplosionSprite();
    bool joinThread() {
        if (this->_thread.joinable()) {
            this->_thread.join();
            std::cout << "JOINED" << std::endl;
            return (true);
        }
        return (false);
    }

    bool isArrived() const {
        return (this->_isArrived);
    }
};

#endif //UNTITLED1_MISSILETHEEAD_HPP
