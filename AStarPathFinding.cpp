//
// Created by adrie on 07/02/2023.
//

#include "AStarPathFinding.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

AStarPathFinding::AStarPathFinding(std::vector<std::vector<MapCell>> &map, MapCell &startCell, MapCell &goalCell)
: _startCell(startCell), _goalCell(goalCell) {
    // THERE SHOULD BE AN ERROR WITH MULTIPLE PATH FIND (EVERY STEP) BECAUSE OF SAME MAP USE
    // I SHOULD BE SETTING AUTOMATICALLY THE GOAL TO THE NEAREST BASE (heuristic distance)
    // --> MAYBE STORE THE BASE COORDINATE INTO MAP OR SMTH
    this->_startCell = startCell;
    this->_goalCell = goalCell;
    std::vector<std::vector<MapCell>> map2(map);
    this->_map = map2;
}

AStarPathFinding::~AStarPathFinding() {
}

bool AStarPathFinding::isInClosedList(MapCell &toFind) {
    int i = 0;
    bool check = false;

    while (i < this->_closeSet.size()) {
            if ((this->_closeSet[i]->getPosX() == toFind.getPosX())
                && (this->_closeSet[i]->getPosY() == toFind.getPosY())) {
                check = true;
                break;
            }
            i++;
    }
    return (check);
}

std::vector<MapCell *> AStarPathFinding::runPathFinding() {
    std::priority_queue<MapCell*, std::vector<MapCell*>, compareCellPriority> openSet;
    std::vector<MapCell*> path;
    std::vector<MapCell*> returnPath;
    this->_startCell.setGlobalCost(0);
    this->_startCell.setHeuristicCost(this->_startCell.getHeuristicFromGoal(&this->_goalCell));
    this->_startCell.setFinalCost(this->_startCell.getGlobalCost() + this->_startCell.getHeuristicCost());
    openSet.push(&this->_startCell);
    // UNCOMMENT FOR DEBUG

    std::cout << "Size X : " << this->_map[0].size() << std::endl;
    std::cout << "Size Y : " << this->_map.size() << std::endl;
    std::cout << "Start cell : " << this->_startCell.getPosX() << " : " << this->_startCell.getPosY() << std::endl;
    std::cout << "Goal cell : " << this->_goalCell.getPosX() << " : " << this->_goalCell.getPosY() << std::endl;

    while (!openSet.empty()) {
        MapCell *cell = openSet.top();
        openSet.pop();
        if (((cell->getPosX() == this->_goalCell.getPosX()) && (cell->getPosY() == this->_goalCell.getPosY()))
        || (cell->getType() == 'B')) {
            std::cout << "Found goal" << std::endl;
            MapCell *pCell = cell;
            while (pCell->getParentCell() != nullptr) {
                returnPath.push_back(pCell);
                pCell = pCell->getParentCell();
            }
            returnPath.push_back(&this->_startCell);
            std::reverse(returnPath.begin(), returnPath.end());
            std::cout << "Return path here" << std::endl;
            return (returnPath);
        }
        this->_closeSet.push_back(cell);
        // TRYING NEIGHBORS
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue;
                int x = cell->getPosX() + i;
                int y = cell->getPosY() + j;
                if (x < 0 || y >= this->_map.size() || y < 0 || x >= this->_map[y].size()) {
                    // SKIPPED : OUT OF MAP
                    continue;
                }
                MapCell *neighbor = &this->_map[y][x];
                if (neighbor->isWalkable() == false) {
                    // SKIPPED : NOT WALKABLE
                    continue;
                }
                if (isInClosedList(*neighbor) == true) {
                    // SKIPPED : ALREADY IN CLOSED LIST
                    continue;
                }
                int testGlobalCost = cell->getGlobalCost() + 1;
                int testFinalCost = testGlobalCost + neighbor->getHeuristicFromGoal(&this->_goalCell);
                if (!openSetContains(openSet, neighbor)) {
                    // ADDING NEIGHBOR
                    neighbor->setGlobalCost(testGlobalCost);
                    neighbor->setHeuristicCost(neighbor->getHeuristicFromGoal(&this->_goalCell));
                    neighbor->setFinalCost(neighbor->getGlobalCost() + neighbor->getHeuristicCost());
                    neighbor->setParentCell(cell);
                    openSet.push(neighbor);
                }
                else {
                    // ALREADY IN OPENSET
                    if (testFinalCost < neighbor->getFinalCost()) {
                        neighbor->setGlobalCost(testGlobalCost);
                        neighbor->setHeuristicCost(neighbor->getHeuristicFromGoal(&this->_goalCell));
                        neighbor->setFinalCost(neighbor->getGlobalCost() + neighbor->getHeuristicCost());
                        neighbor->setParentCell(cell);
                    }
                }
            }
        }
    }
    return (path);
}

bool        AStarPathFinding::openSetContains(std::priority_queue<MapCell*, std::vector<MapCell*>, compareCellPriority>& openSet, MapCell* cell) {
    std::priority_queue<MapCell*, std::vector<MapCell*>, compareCellPriority> copy = openSet;
    while (!copy.empty()) {
        MapCell* top = copy.top();
        copy.pop();
        if ((top->getPosX() == cell->getPosX()) && (top->getPosY() == cell->getPosY())) {
            return true;
        }
    }
    return false;
}