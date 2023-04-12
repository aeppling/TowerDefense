//
// Created by adrie on 12/04/2023.
//

#ifndef UNTITLED1_MISSILETHEEAD_HPP
#define UNTITLED1_MISSILETHEEAD_HPP

#include "../TDGraphics/SFMLMissileLoader.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

void shootMissile(SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow& window,
                  const sf::Vector2f& startPosition, const sf::Vector2f& endPosition, int cellSize, float speed);

#endif //UNTITLED1_MISSILETHEEAD_HPP
