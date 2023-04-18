//
// Created by adrie on 05/04/2023.
//

#ifndef UNTITLED1_SPRITESHOLDER_HPP
#define UNTITLED1_SPRITESHOLDER_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include "SFMLSprite.hpp"
#include "SFMLLoader.hpp"
#include "../TDMap/TDMap.hpp"

class TDMap;

class SpritesHolder {
private:
    std::vector<std::shared_ptr<SFMLSprite>>  _wallSprite;
    std::vector<std::shared_ptr<SFMLSprite>>  _walkableSprite;
    std::vector<std::shared_ptr<SFMLSprite>>  _notWalkableSprite;
    std::vector<std::shared_ptr<SFMLSprite>>  _baseSprite;
    std::vector<std::shared_ptr<SFMLSprite>>  _spawnSprite;
public:
    SpritesHolder() {};
    ~SpritesHolder() {};
    void                                      updateSpriteFromTypeAndPosition(char type, int posX, int posY,
                                                              SFMLLoader &sfmlLoader, int cellSize, char newType);
    std::shared_ptr<SFMLSprite>               getSpriteFromPosition(int posX, int posY);
    std::shared_ptr<SFMLSprite>               getNotWalkableSpriteFromPosition(int posX, int posY);
    std::shared_ptr<SFMLSprite>               getWallSpriteFromPosition(int posX, int posY);
    void                                      setSpriteFromTypeAndPosition(MapCell *mapCell, TDMap *map, SFMLLoader &sfmlLoader, int cellSize);
    void                                      displayDebug();
    void                                      displayMap(sf::RenderWindow &window, int cellSize, SFMLLoader &sfmlLoaderMap);
};

#endif //UNTITLED1_SPRITESHOLDER_HPP
