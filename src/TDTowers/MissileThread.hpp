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
    bool _isArrived;
public:
    MissileThread();
    ~MissileThread() {};
    void shootMissile(SFMLMissileLoader &sfmlMissileLoader,
                      const sf::Vector2f& startPosition, const sf::Vector2f& endPosition, int cellSize, float speed);

    void join() {
        // Join the thread
 /*       if (t && t->joinable()) {
            t->join();
        }*/
    }

    bool isFinished() const {
        // Check if the thread has finished
    //    return finished;
    }
};

#endif //UNTITLED1_MISSILETHEEAD_HPP
