//
// Created by adrie on 29/03/2023.
//

#include "SizeRatioCalculator.hpp"
#include <algorithm>

int getCellSize(int winSizeX, int winSizeY, int mapSizeX, int mapSizeY) {
    int smallerWinSize = std::min(winSizeX, winSizeY);
    int largerMapSize = std::max(mapSizeY, mapSizeX);
    int cellSize = std::min(smallerWinSize / largerMapSize, smallerWinSize / largerMapSize);

    if ((mapSizeY > 30) || (mapSizeX > 30))
        cellSize = cellSize / 1.1;
    if ((mapSizeY > 40) || (mapSizeX > 40))
        cellSize = cellSize / 1.2;
    if ((mapSizeY > 60) || (mapSizeX > 60))
        cellSize = cellSize / 1.3;
    return (cellSize);
}

mouseCoordinates getMouseCellCoordinate(TDMap &map, sf::RenderWindow &window) {
    sf::Vector2i mousePositionScreen = sf::Mouse::getPosition();
    sf::Vector2i windowPositionScreen = window.getPosition();
    sf::Vector2i mousePositionMap = mousePositionScreen - windowPositionScreen;
    mousePositionMap.x -= window.getViewport(window.getView()).left;
    mousePositionMap.y -= window.getViewport(window.getView()).top;

    int cellSize = getCellSize(window.getSize().x, window.getSize().y, map.getSizeX(), map.getSizeY());
    cellSize = cellSize + 0.5; // I DON'T KNOW WHY BUT C'EST DéCalé SINON :c
    int rowIndex = (mousePositionMap.y / cellSize) - 1; // SAME SHIT
    int colIndex = mousePositionMap.x / cellSize;
    mouseCoordinates mouseCoord;
    mouseCoord.posY = rowIndex;
    mouseCoord.posX = colIndex;
    return (mouseCoord);
}