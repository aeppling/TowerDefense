//
// Created by adrie on 06/02/2023.
//

#ifndef UNTITLED1_MAPCELL_HPP
#define UNTITLED1_MAPCELL_HPP

#include <ostream>

class MapCell {
private:
    char             _type;
    unsigned int     _posX;
    unsigned int     _posY;
    unsigned int     _finalCost = 999999;
    unsigned int     _globalCost = 999999;
    unsigned int     _heuristicCost = 999999;
    MapCell          *_parentCell = nullptr;
public:
    // (DE)CONSTRUCTOR AND OVERLOAD
    MapCell(char type, int posX, int posY, int globalCost, int heuristicCost, MapCell *parentCell);
    MapCell(char type, int posX, int posY);
    ~MapCell();
    MapCell(const MapCell& src) :   _type(src._type), _finalCost(src._finalCost),
                                    _globalCost(src._globalCost), _heuristicCost(src._heuristicCost),
                                    _posX(src._posX), _posY(src._posY) {}
    friend std::ostream &operator<<(std::ostream &ostream, const MapCell &cell);
    struct ByFValue
    {
        bool operator()(const MapCell &a, const MapCell &b) const
        {
            return a._finalCost < b._finalCost;
        }
    };
    // GETTER AND SETTER
    void         setParentCell(MapCell *parentCell) { this->_parentCell = parentCell; }
    MapCell      *getParentCell() { return(this->_parentCell); };
    char         getType() { return(this->_type); };
    unsigned int getFinalCost() { return(this->_finalCost); };
    unsigned int getGlobalCost() { return(this->_globalCost); };
    unsigned int getHeuristicCost() { return(this->_heuristicCost); };
    void         setType(char newType) { this->_type = newType; };
    void         setFinalCost(unsigned int finalCost) { this->_finalCost = finalCost; };
    void         setGlobalCost(unsigned int globalCost) { this->_globalCost = globalCost; };
    void         setHeuristicCost(unsigned int heuristicCost) { this->_heuristicCost = heuristicCost; };
    unsigned int getPosX() { return(this->_posX); };
    unsigned int getPosY() { return(this->_posY); };
    void         setPosX(unsigned int posX) { this->_posX = posX; };
    void         setPosY(unsigned int posY) { this->_posY = posY; };
    //
    //OTHERS
    bool         isWalkable();
    bool         isWall();
    int          getHeuristicFromGoal(MapCell* goal);
    //
};


#endif //UNTITLED1_MAPCELL_HPP
