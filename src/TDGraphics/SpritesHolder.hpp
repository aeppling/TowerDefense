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
#include "../TDGraphics/SFMLDecorationLoader.hpp"

class TDMap;

class SpritesHolder {
private:
    std::vector<std::shared_ptr<SFMLSprite>>  _wallSprite;
    std::vector<std::shared_ptr<SFMLSprite>>  _walkableSprite;
    std::vector<std::shared_ptr<SFMLSprite>>  _notWalkableSprite;
    std::vector<std::shared_ptr<SFMLSprite>>  _decorationSprite;
    std::vector<std::shared_ptr<SFMLSprite>>  _baseSprite;
    std::vector<std::shared_ptr<SFMLSprite>>  _spawnSprite;
    // Tiles overlap their neighbours by a few pixels, so draw order is what
    // hides the seams. Sprites must stay sorted row by row (posY, then posX).
    static void                               insertSorted(std::vector<std::shared_ptr<SFMLSprite>> &list,
                                                           const std::shared_ptr<SFMLSprite> &sprite);
public:
    SpritesHolder() {};
    ~SpritesHolder() {};
    // useHeightTile mirrors the choice made when the map was first built: an
    // 'X' cell sitting on top of an 'F' cell uses the taller path tile.
    void                                      updateSpriteFromTypeAndPosition(char type, int posX, int posY,
                                                              SFMLLoader &sfmlLoader, int cellSize, char newType,
                                                              bool useHeightTile = false);
    std::shared_ptr<SFMLSprite>               getSpriteFromPosition(int posX, int posY);
    std::shared_ptr<SFMLSprite>               getNotWalkableSpriteFromPosition(int posX, int posY);
    std::shared_ptr<SFMLSprite>               getWallSpriteFromPosition(int posX, int posY);
    void                                      setSpriteFromTypeAndPosition(MapCell *mapCell, TDMap *map, SFMLLoader &sfmlLoader, int cellSize, SFMLDecorationLoader &sfmlDecorationLoader, int planet);
    void                                      displayDebug();
    void                                      displayMap(sf::RenderWindow &window, int cellSize, SFMLLoader &sfmlLoaderMap);
};

#endif //UNTITLED1_SPRITESHOLDER_HPP
