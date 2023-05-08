//
// Created by adrie on 12/04/2023.
//

#include "MissileThread.hpp"
#include <math.h>
#include <mutex>

std::mutex mutexSprite;

MissileThread::MissileThread() : _isArrived(false) {
    
}

void MissileThread::animateExplosion() {
    sf::Vector2f newOrigin(this->_explosionSprite.getLocalBounds().height / 2.f, this->_explosionSprite.getLocalBounds().height / 2.f);
    this->_explosionSprite.setOrigin(newOrigin);
    int numSprites = this->_explosionSprite.getTexture()->getSize().x / this->_explosionSprite.getTexture()->getSize().y;
    int spriteWidth = this->_explosionSprite.getTexture()->getSize().y;
    sf::IntRect textureRect(0, 0, 80, 80);
    this->_explosionSprite.setTextureRect(textureRect);
    this->_explosionSprite.setScale(0.8, 0.8);
    int displayedSprite = 0;
    // Check if animation time exceeds the time for one sprite
    while (displayedSprite != numSprites) {
        textureRect.left += spriteWidth;
        this->_explosionSprite.setTextureRect(textureRect);
        displayedSprite++;
        if (displayedSprite != numSprites)
            sf::sleep(sf::milliseconds(10));
    }
}

void MissileThread::shootMissile(SFMLMissileLoader &sfmlMissileLoader, const sf::Vector2f &startPosition,
                                 const sf::Vector2f &endPosition, int &cellSize, float &speed) {
    speed = speed / 1000;
    if (this->_style == "BasicTower")
        this->_sprite.setTexture(*sfmlMissileLoader.getBasic());
    else if (this->_style == "AttackSpeedTower")
        this->_sprite.setTexture(*sfmlMissileLoader.getSpeed());
    else if (this->_style == "AntiAirTower")
        this->_sprite.setTexture(*sfmlMissileLoader.getAntiAir());
    else if (this->_style == "SlowTower")
        this->_sprite.setTexture(*sfmlMissileLoader.getSlow());
    else if (this->_style == "SniperTower")
        this->_sprite.setTexture(*sfmlMissileLoader.getSniper());
    else
        this->_sprite.setTexture(*sfmlMissileLoader.getSpeed());
    float scaleFactor = static_cast<float>(cellSize) / static_cast<float>(this->_sprite.getTexture()->getSize().x);
    sf::IntRect textureRect(0, 0, this->_sprite.getTexture()->getSize().x, this->_sprite.getTexture()->getSize().y);
    if ((this->_style == "AntiAirTower") || (this->_style == "SniperTower"))
        this->_sprite.setScale(scaleFactor * 4, scaleFactor * 4);
    else if (this->_style == "SlowTower")
        this->_sprite.setScale(scaleFactor * 3, scaleFactor * 3);
    else
        this->_sprite.setScale(scaleFactor * 2, scaleFactor * 2);
    this->_sprite.setTextureRect(textureRect);
    sf::Vector2f newOrigin(this->_sprite.getLocalBounds().width / 2.f, this->_sprite.getLocalBounds().height / 2.f);
    this->_sprite.setOrigin(newOrigin);
    std::unique_lock<std::mutex> lock(mutexSprite);
    this->_sprite.setPosition(startPosition);
    mutexSprite.unlock();
    sf::Vector2f direction = endPosition - startPosition;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f unitDirection = direction / distance;
    float elapsedTime = 0.0f;
    // SETTINGS ROTATION
    float angle = atan2(direction.y, direction.x) * 180 / 3.14159f;
    this->_sprite.setRotation(angle);
    // PLAYING SHOT
    while (elapsedTime < distance / speed)
    {
        elapsedTime += 0.01f; // Update elapsed time with an arbitrary value (you can adjust this for smoother animation)
        sf::Vector2f displacement = unitDirection * speed * elapsedTime;
        mutexSprite.lock();
        this->_sprite.setPosition(startPosition + displacement);
        mutexSprite.unlock();
    }
    this->_sprite.setPosition(endPosition);
    // PLAY BOOM
    this->_sprite.setPosition(5000, 5000);
    this->_explosionSprite.setPosition(endPosition);
    this->animateExplosion();
    this->_isArrived = true;
}

void MissileThread::initStyle(SFMLMissileLoader &sfmlMissileLoader)
{
    this->_explosionSprite.setTexture(*sfmlMissileLoader.getExplosion1());
    if (this->_style == "AntiAirTower") {
        this->_explosionSprite.setScale(1.2, 1.2);
        this->_explosionSprite.setColor(sf::Color::Yellow);
    }
    else if (this->_style == "BasicTower") {
        this->_explosionSprite.setScale(0.7, 0.7);
    }
    else if (this->_style == "AttackSpeedTower") {
        this->_explosionSprite.setScale(0.3, 0.3);
        this->_explosionSprite.setColor(sf::Color::Yellow);
    }
    else if (this->_style == "SlowTower") {
        this->_explosionSprite.setScale(0.5, 0.5);
        this->_explosionSprite.setColor(sf::Color::Blue);
    }
    else if (this->_style == "SniperTower") {
        this->_explosionSprite.setScale(1, 1);
        this->_explosionSprite.setColor(sf::Color::Magenta);
    }
    else {
        this->_explosionSprite.setScale(0.5, 0.5);
    }
}

void MissileThread::startThread(SFMLMissileLoader &sfmlMissileLoader, const sf::Vector2f& startPosition,
                                const sf::Vector2f& endPosition, int cellSize, float speed, std::string style)
{
    this->_style = style;
    this->initStyle(sfmlMissileLoader);
    this->_explosionSprite.setPosition(-500, -500);
    this->_thread = std::thread(&MissileThread::shootMissile, this, std::ref(sfmlMissileLoader), startPosition, endPosition, std::ref(cellSize), std::ref(speed));
    this->_thread.detach();
}

sf::Sprite MissileThread::getSprite() {
   return (this->_sprite);
}

sf::Sprite MissileThread::getExplosionSprite() {
    return (this->_explosionSprite);
}