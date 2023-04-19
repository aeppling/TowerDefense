//
// Created by adrie on 18/04/2023.
//

#ifndef UNTITLED1_SFMLCOINANIMATION_HPP
#define UNTITLED1_SFMLCOINANIMATION_HPP

#include "SFML/Graphics.hpp"

class SFMLCoinAnimation {
private:
    sf::Texture             _basicCoin;
    sf::Font                _textFont;
    std::vector<sf::Sprite> _activeList;
    std::vector<sf::Text>   _activeText;
public:
    SFMLCoinAnimation();
    ~SFMLCoinAnimation() {};

    // BASIC FUNCTION
    sf::Texture *getBasicCoin() { return (&this->_basicCoin); }
    void        launchCoinsAnimation(int cellSize, int posX, int posY, int amount, bool isWon);
    void        animateCoin(int index);
    void        animateAmount(const int index);

    //FOR PARSING IN GAME.CPP
    int         getTotalCoins() { return (this->_activeList.size()); };
    int         getTotalText() { return (this->_activeText.size()); };
    sf::Sprite  getCoinFromIndex(int index) { return (this->_activeList.at(index)); };
    void        clear() { this->_activeList.clear(); this->_activeText.clear(); };
    sf::Text    getTextFromIndex(int index) { return (this->_activeText.at(index)); };
};

#endif //UNTITLED1_SFMLCOINANIMATION_HPP
