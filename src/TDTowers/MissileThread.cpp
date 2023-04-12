//
// Created by adrie on 12/04/2023.
//

#include "MissileThread.hpp"
#include <math.h>
#include <mutex>

sf::Mutex windowMutex;

void shootMissile(SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow& window, const sf::Vector2f& startPosition, const sf::Vector2f& endPosition, int cellSize, float speed)
{
    sf::Sprite sprite(*sfmlMissileLoader.getSpeed());
    float scaleFactor = static_cast<float>(cellSize) / static_cast<float>(sprite.getTexture()->getSize().x);
    sf::IntRect textureRect(0, 0, sprite.getTexture()->getSize().x, sprite.getTexture()->getSize().y);
    sprite.setScale(scaleFactor * 1, scaleFactor * 1);
    sprite.setTextureRect(textureRect);
    sf::Vector2f newOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    sprite.setOrigin(newOrigin);
//    sprite.setPosition((startPosition.x * cellSize) + cellSize/2, (startPosition.y * cellSize) + cellSize / 2);
    sprite.setPosition(startPosition);

    sf::Vector2f direction = endPosition - startPosition;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f unitDirection = direction / distance;
    float elapsedTime = 0.0f;

    while (elapsedTime < distance / speed)
    {
        elapsedTime += 0.01f; // Update elapsed time with an arbitrary value (you can adjust this for smoother animation)
        sf::Vector2f displacement = unitDirection * speed * elapsedTime;
        sprite.setPosition(startPosition + displacement);
        windowMutex.lock();
      //  window.draw(sprite);
        windowMutex.unlock();
    }
    // Set the sprite to the end position after animation is finished to ensure accurate positioning
    sprite.setPosition(endPosition);
   //window.draw(sprite);
}