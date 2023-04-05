//
// Created by adrie on 05/04/2023.
//

#ifndef UNTITLED1_SPRITESHOLDER_HPP
#define UNTITLED1_SPRITESHOLDER_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include "SFMLSprite.hpp"

class SpritesHolder {
private:
    std::vector<std::shared_ptr<SFMLSprite>>  _wallSprite;
    std::vector<std::shared_ptr<SFMLSprite>>  _walkableSprite;
    std::vector<std::shared_ptr<SFMLSprite>>  _notWalkableSprite;
public:
    SpritesHolder();
    ~SpritesHolder();
    std::shared_ptr<SFMLSprite>               getSpriteFromPosition(int posX, int posY);
    void                                      setSpriteFromPosition(int posX, int posY, std::shared_ptr<SFMLSprite>);
};

#endif //UNTITLED1_SPRITESHOLDER_HPP
