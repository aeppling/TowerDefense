//
// Created by adrie on 29/03/2023.
//

#ifndef UNTITLED1_SIZERATIOCALCULATOR_HPP
#define UNTITLED1_SIZERATIOCALCULATOR_HPP

#include "../TDMap/TDMap.hpp"

typedef struct mouseCoordinates {
    int posX;
    int posY;
} mouseCoordinates;

int getCellSize(int winSizeX, int winSizeY, int mapSizeX, int mapSizeY);
mouseCoordinates getMouseCellCoordinate(TDMap &map, sf::RenderWindow &window);

#endif //UNTITLED1_SIZERATIOCALCULATOR_HPP
