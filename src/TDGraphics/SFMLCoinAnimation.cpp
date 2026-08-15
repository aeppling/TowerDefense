//
// Created by adrie on 18/04/2023.
//

#include <iostream>
#include <functional>
#include <thread>

#include "SFMLCoinAnimation.hpp"
#include "../TDGame/usefullStruct.hpp"

// sf::Color::a is a Uint8: "a - 5" wraps around to 250 instead of going
// negative, which made the coins and the text flash back to fully opaque.
static sf::Uint8    fadeOut(sf::Uint8 alpha, sf::Uint8 step) {
    return (alpha > step ? alpha - step : 0);
}

SFMLCoinAnimation::SFMLCoinAnimation() {
    if (!(this->_basicCoin.loadFromFile("ressources/Sprites/Fx/MonedaD.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_textFont.loadFromFile("ressources/Fonts/PixelIntv-OPxd.ttf")))
        std::cout << "Error on loading texture..." << std::endl;
}

void        SFMLCoinAnimation::animateAmount(const int index) {
    int repeat = 0;
    sf::Color color;
    sf::Color colorOut;
    {
        std::lock_guard<std::mutex> lock(this->_mutex);
        if ((index < 0) || (index >= (int)this->_activeText.size()))
            return;
        color = this->_activeText.at(index).getFillColor();
        colorOut = this->_activeText.at(index).getOutlineColor();
        color.a = 255;
        colorOut.a = 255;
        this->_activeText.at(index).setFillColor(color);
    }
    while (repeat <= 20) {
        sf::sleep(sf::milliseconds(70));
        color.a = fadeOut(color.a, 5);
        colorOut.a = fadeOut(colorOut.a, 7);
        std::lock_guard<std::mutex> lock(this->_mutex);
        // The list can be cleared between waves while this thread runs.
        if ((index < 0) || (index >= (int)this->_activeText.size()))
            return;
        this->_activeText.at(index).setFillColor(color);
        this->_activeText.at(index).setOutlineColor(colorOut);
        this->_activeText.at(index).setPosition(this->_activeText.at(index).getPosition().x,
                                                this->_activeText.at(index).getPosition().y - 0.7);
        repeat++;
    }
    std::lock_guard<std::mutex> lock(this->_mutex);
    if ((index >= 0) && (index < (int)this->_activeText.size()))
        this->_activeText.at(index).setPosition(-50, -50);
}

void        SFMLCoinAnimation::animateCoin(const int index) {
    int numSprites = 0;
    int spriteWidth = 0;
    sf::Color color;
    {
        std::lock_guard<std::mutex> lock(this->_mutex);
        if ((index < 0) || (index >= (int)this->_activeList.size()))
            return;
        numSprites = this->_activeList.at(index).getTexture()->getSize().x / this->_activeList.at(index).getTexture()->getSize().y;
        spriteWidth = this->_activeList.at(index).getTexture()->getSize().y;
        color = this->_activeList.at(index).getColor();
        color.a = 255;
        this->_activeList.at(index).setColor(color);
        this->_activeList.at(index).setTextureRect(sf::IntRect(0, 0, spriteWidth, spriteWidth));
    }
    sf::IntRect textureRect(0, 0, spriteWidth, spriteWidth);
    int repeat = 0;
    while (repeat <= 6) {
        int displayedSprite = 0;
        while (displayedSprite != numSprites) {
            textureRect.left += spriteWidth;
            displayedSprite++;
            if (displayedSprite != numSprites)
                sf::sleep(sf::milliseconds(70));
            color.a = fadeOut(color.a, 5);
            std::lock_guard<std::mutex> lock(this->_mutex);
            if ((index < 0) || (index >= (int)this->_activeList.size()))
                return;
            this->_activeList.at(index).setTextureRect(textureRect);
            this->_activeList.at(index).setColor(color);
            this->_activeList.at(index).setPosition(this->_activeList.at(index).getPosition().x,
                                                    this->_activeList.at(index).getPosition().y - 0.5);
        }
        textureRect.left = 0;
        repeat++;
    }
    std::lock_guard<std::mutex> lock(this->_mutex);
    if ((index >= 0) && (index < (int)this->_activeList.size())) {
        this->_activeList.at(index).setTextureRect(textureRect);
        this->_activeList.at(index).setPosition(-50, -50);
    }
}

void        SFMLCoinAnimation::launchCoinsAnimation(int cellSize, int posX, int posY, int amount, bool isWon) {
    // CREATE NEW COIN SPRITE
    sf::Sprite newSprite;
    newSprite.setTexture(this->_basicCoin);
    float scaleFactor = static_cast<float>(cellSize) / static_cast<float>(newSprite.getTexture()->getSize().x);
    sf::IntRect textureRect(0, 0, newSprite.getTexture()->getSize().y, newSprite.getTexture()->getSize().y);
    newSprite.setScale(scaleFactor * 4, scaleFactor * 4);
    newSprite.setTextureRect(textureRect);
    sf::Vector2f newOrigin(newSprite.getLocalBounds().width / 2.f, newSprite.getLocalBounds().height / 2.f);
    newSprite.setOrigin(newOrigin);
    newSprite.setPosition((posX * cellSize) + cellSize/2 + _GAME_POSITION_X, posY * cellSize + (_GAME_POSITION_Y - cellSize/2));
    // CREATE NEW TEXT SPRITE
    sf::Text amountText;
    amountText.setFont(this->_textFont);
    if (isWon == true) {
        amountText.setString("+ " + std::to_string(amount) + " po");
        amountText.setFillColor(sf::Color::Green);
    }
    else {
        amountText.setString("- " + std::to_string(amount) + " po");
        amountText.setFillColor(sf::Color::Red);
    }
    amountText.setPosition((posX * cellSize) + cellSize + 8+ _GAME_POSITION_X, (posY * cellSize) - cellSize + _GAME_POSITION_Y);
    amountText.setCharacterSize(17);
    amountText.setOutlineThickness(1);
    amountText.setOutlineColor(sf::Color::Black);

    int indexSprite = 0;
    int indexText = 0;
    {
        std::lock_guard<std::mutex> lock(this->_mutex);
        this->_activeList.push_back(newSprite);
        indexSprite = this->_activeList.size() - 1;
        this->_activeText.push_back(amountText);
        indexText = this->_activeText.size() - 1;
    }
    // LAUNCH THREADS
    std::thread newThreadSprite(&SFMLCoinAnimation::animateCoin, this, indexSprite);
    newThreadSprite.detach();
    std::thread newThreadText(&SFMLCoinAnimation::animateAmount, this, indexText);
    newThreadText.detach();
}
