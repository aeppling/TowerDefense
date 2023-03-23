//
// Created by adrie on 07/02/2023.
//

#ifndef UNTITLED1_ASTARPATHFINDING_HPP
#define UNTITLED1_ASTARPATHFINDING_HPP

#include <stdbool.h>
#include <queue>
#include <memory>

#include "TDMap.hpp"

struct compareCellPriority {
    bool operator()(MapCell* a, MapCell* b) const {
        return a->getFinalCost() > b->getFinalCost();
    }
};

class AStarPathFinding {
private:
    MapCell &_startCell;
    MapCell &_goalCell;
    std::vector<std::vector<MapCell>> _map;
    std::vector<MapCell *> _closeSet; // cells already evaluated
public:
    AStarPathFinding(std::vector<std::vector<MapCell>> &map, MapCell &startCell, MapCell &goalCell);

    ~AStarPathFinding();

    std::shared_ptr<std::vector<MapCell *>> runPathFinding(std::shared_ptr<std::vector<MapCell*>> pathToFill);

    bool isInClosedList(MapCell &toFind);
    bool openSetContains(std::priority_queue<MapCell *, std::vector<MapCell *>, compareCellPriority> &openSet, MapCell *cell);
};

#endif //UNTITLED1_ASTARPATHFINDING_HPP
