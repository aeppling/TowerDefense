//
// Created by adrie on 18/04/2023.
//

#ifndef UNTITLED1_SFMLCOINANIMATION_HPP
#define UNTITLED1_SFMLCOINANIMATION_HPP

#include "SFML/Graphics.hpp"

#include <deque>
#include <mutex>

class SFMLCoinAnimation {
private:
    sf::Texture             _basicCoin;
    sf::Font                _textFont;
    // deque, not vector: growing a vector reallocates its buffer, which the
    // detached animation threads were reading from at the same time. A deque
    // keeps existing elements put when it grows.
    std::deque<sf::Sprite>  _activeList;
    std::deque<sf::Text>    _activeText;
    // Guards both containers: the main thread appends while the animation
    // threads and the render thread read.
    mutable std::mutex      _mutex;
public:
    SFMLCoinAnimation();
    ~SFMLCoinAnimation() {};

    // BASIC FUNCTION
    sf::Texture *getBasicCoin() { return (&this->_basicCoin); }
    void        launchCoinsAnimation(int cellSize, int posX, int posY, int amount, bool isWon);
    void        animateCoin(int index);
    void        animateAmount(const int index);

    //FOR PARSING IN GAME.CPP
    int         getTotalCoins() { std::lock_guard<std::mutex> l(this->_mutex); return (this->_activeList.size()); };
    int         getTotalText() { std::lock_guard<std::mutex> l(this->_mutex); return (this->_activeText.size()); };
    // Count and elements are fetched in separate calls, so guard against the
    // list changing in between instead of letting at() throw.
    sf::Sprite  getCoinFromIndex(int index) {
        std::lock_guard<std::mutex> l(this->_mutex);
        if ((index < 0) || (index >= (int)this->_activeList.size())) {
            sf::Sprite empty; empty.setPosition(-5000, -5000); return (empty);
        }
        return (this->_activeList.at(index));
    };
    sf::Text    getTextFromIndex(int index) {
        std::lock_guard<std::mutex> l(this->_mutex);
        if ((index < 0) || (index >= (int)this->_activeText.size())) {
            sf::Text empty; empty.setPosition(-5000, -5000); return (empty);
        }
        return (this->_activeText.at(index));
    };
    void        clear() {
        std::lock_guard<std::mutex> l(this->_mutex);
        this->_activeList.clear(); this->_activeText.clear();
    };
};

#endif //UNTITLED1_SFMLCOINANIMATION_HPP
