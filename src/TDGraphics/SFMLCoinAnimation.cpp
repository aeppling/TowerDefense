//
// Created by adrie on 18/04/2023.
//

#include <iostream>
#include <functional>
#include <thread>

#include "SFMLCoinAnimation.hpp"
#include "../TDGame/usefullStruct.hpp"

SFMLCoinAnimation::SFMLCoinAnimation() {
    if (!(this->_basicCoin.loadFromFile("Sprites/MyTiles/MonedaD.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_textFont.loadFromFile("Fonts/PixelIntv-OPxd.ttf")))
        std::cout << "Error on loading texture..." << std::endl;
}

void        SFMLCoinAnimation::animateAmount(const int index) {
    int repeat = 0;
    sf::Color color = this->_activeText.at(index).getColor();
    sf::Color colorOut = this->_activeText.at(index).getOutlineColor();
    color.a = 255;
    colorOut.a = 255;
    this->_activeText.at(index).setColor(color);
    while (repeat <= 20) {
        sf::sleep(sf::milliseconds(70));
        color.a = color.a - 5;
        if (colorOut.a < 0)
            colorOut.a = 0;
        else
            colorOut.a = colorOut.a - 7;
        this->_activeText.at(index).setColor(color);
        this->_activeText.at(index).setOutlineColor(colorOut);
        this->_activeText.at(index).setPosition(this->_activeText.at(index).getPosition().x ,
                                                    this->_activeText.at(index).getPosition().y - 0.7);
        repeat++;
    }
    this->_activeText.at(index).setPosition(-50, -50);
}

void        SFMLCoinAnimation::animateCoin(const int index) {
        int numSprites = this->_activeList.at(index).getTexture()->getSize().x / this->_activeList.at(index).getTexture()->getSize().y;
        int spriteWidth = this->_activeList.at(index).getTexture()->getSize().y;
        sf::IntRect textureRect(0, 0, spriteWidth, spriteWidth);
        this->_activeList.at(index).setTextureRect(textureRect);
        int repeat = 0;
        sf::Color color = this->_activeList.at(index).getColor();
        color.a = 255;
        this->_activeList.at(index).setColor(color);
        while (repeat <= 6) {
            int displayedSprite = 0;
            // Check if animation time exceeds the time for one sprite
            while (displayedSprite != numSprites) {
                textureRect.left += spriteWidth;
                this->_activeList.at(index).setTextureRect(textureRect);
                displayedSprite++;
                if (displayedSprite != numSprites)
                    sf::sleep(sf::milliseconds(70));
                color.a = color.a - 5;
                this->_activeList.at(index).setColor(color);
                this->_activeList.at(index).setPosition(this->_activeList.at(index).getPosition().x ,
                                                        this->_activeList.at(index).getPosition().y - 0.5);

            }
            textureRect.left = 0;
            repeat++;
        }
        this->_activeList.at(index).setTextureRect(textureRect);
        this->_activeList.at(index).setPosition(-50, -50);
}

void        SFMLCoinAnimation::launchCoinsWon(int cellSize, int posX, int posY, int amount) {
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
    this->_activeList.push_back(newSprite);
    const int indexSprite = this->_activeList.size() - 1;
    // CREATE NEW TEXT SPRITE
    sf::Text amountText;
    amountText.setFont(this->_textFont);
    amountText.setString("+ " + std::to_string(amount) + " po");
    sf::Vector2f newOriginText(amountText.getLocalBounds().width / 2.f, amountText.getLocalBounds().height / 2.f);
    newSprite.setOrigin(newOriginText);
    amountText.setPosition((posX * cellSize) + cellSize + 8+ _GAME_POSITION_X, (posY * cellSize) - cellSize + _GAME_POSITION_Y);
    amountText.setCharacterSize(17);
    amountText.setOutlineThickness(1);
    amountText.setOutlineColor(sf::Color::Black);
    amountText.setFillColor(sf::Color::Green);
    this->_activeText.push_back(amountText);
    const int indexText = this->_activeText.size() - 1;
    // LAUNCH THREADS
    std::thread newThreadSprite(&SFMLCoinAnimation::animateCoin, this, indexSprite);
    newThreadSprite.detach();
    std::thread newThreadText(&SFMLCoinAnimation::animateAmount, this, indexText);
    newThreadText.detach();
}

void        SFMLCoinAnimation::eraseCoin(int index) {
    this->_activeList.erase(this->_activeList.begin() + index);
}