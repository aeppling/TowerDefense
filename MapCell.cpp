//
// Created by adrie on 06/02/2023.
//

#include "MapCell.hpp"

MapCell::MapCell(char type, int posX, int posY, int globalCost, int heuristicCost, MapCell *parentCell)
    : _type(type), _posX(posX), _posY(posY), _globalCost(globalCost), _heuristicCost(heuristicCost), _parentCell(parentCell)
{
    this->_finalCost = globalCost + heuristicCost;
}

MapCell::MapCell(char type, int posX, int posY) : _type(type), _posX(posX), _posY(posY), _finalCost(0),
                                                  _globalCost(0), _heuristicCost(0) {
}

MapCell::~MapCell() {

}

int MapCell::getHeuristicFromGoal(MapCell* goal) {
    int distX, distY;
    distX = this->_posX - goal->getPosX();
    distY = this->_posY - goal->getPosY();
    return ((distX*distX) + (distY*distY));
}

bool MapCell::isWalkable() {
    // ADD CONDITIONS HERE FOR TRANSPARENT OR NOT UNITS
    if ((this->_type == 'X') || (this->_type == 'B') || (this->_type == 'S'))
        return (true);
    else
        return (false);
}

std::ostream &operator<<(std::ostream &ostream, const MapCell &cell) {
    ostream << cell._type;
    return (ostream);
}

