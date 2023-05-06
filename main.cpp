#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <mutex>

#include "src/TDGraphics/SFMLLoader.hpp"
#include "src/TDMap/mapParser.hpp"
#include "src/TDMap/AStarPathFinding.hpp"
#include "src/TDUnits/TDUnit.hpp"
#include "src/TDGame/RetrieveLevel.hpp"
#include "src/TDGame/SizeRatioCalculator.hpp"
#include "src/TDGame/Game.hpp"
#include "src/TDPlayer/TDPlayer.hpp"
#include "src/TDSounds/SFMainSoundLoader.hpp"
#include "src/TDSounds/SFMainSoundPlayer.hpp"

bool isInPathFound(int x, int y, std::vector<MapCell*> path) {
    int i = 0;
    while (i != path.size()) {
        if ((path[i]->getPosX() == x) && (path[i]->getPosY() == y))
            return true;
        i++;
    }
    return (false);
}

void displayDebugMap(std::vector<std::vector<MapCell>> *map, std::vector<MapCell*> path) {
    int x;
    int y = 0;

    while (y != map->size()) {
        x = 0;
        while (x != (*map)[y].size()) {
            if (isInPathFound((*map)[y][x].getPosX(), (*map)[y][x].getPosY(), path) == true)
                std::cout << "S ";
            else
                std::cout << (*map)[y][x].getType() << " ";
            x++;
        }
        std::cout << std::endl;
        y++;
    }
    std::cout << "END OF DEBUG DISPLAY" << std::endl << std::endl;

}


/* UNCOMMENT TO DEBUG PATH FINDING
 std::cout << "START CELL 1 x/y : " << (*nmap)[0][1].getPosX() << " : " << (*nmap)[0][1].getPosY() << std::endl;
 std::cout << "GOAL CELL 1 x/y : " << (*nmap)[10][10].getPosX() << " : " << (*nmap)[10][10].getPosY() << std::endl;
 AStarPathFinding pathFinder((*nmap), (*nmap)[0][1], (*nmap)[20][29]);
 std::vector<MapCell*> path = pathFinder.runPathFinding();
 int i = 0;
 while (i != path.size()) {
     std::cout << path[i]->getPosX() << " : " << path[i]->getPosY() << " | ";
     i++;
 }
 std::cout << std::endl;
 displayDebugMap((nmap), path);
 if (path.empty()) {
     std::cout << "NO PATH FOUND !!!" << std::endl;
 }
*/

int main() {
    // SETTING SOUNDS
    SFMainSoundLoader mainSoundLoader;
    // SETTING WINDOW AND MAP
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Window", sf::Style::Default);
    window.setActive(true);
    SFMLLoader sfmlLoader;
    // CREATE GAME OBJET
    TDPlayer *playerOne = new TDPlayer("Joueur1");
    SFMainSoundPlayer sfSoundPlayer(mainSoundLoader);
    sfSoundPlayer.playGameMusic1();
    Game currentGame(1, 1, playerOne, sfSoundPlayer);
    try {
        if (currentGame.launch(sfmlLoader, window) == -1) {
            std::cout << "Error on map initialisation" << std::endl;
            return (-1);
        }
    } catch (const std::out_of_range& ex) {
        std::cout << "Exception at line : " << __LINE__ << " in file : "<< __FILE__<< " : " << ex.what() << std::endl;
    }
    // WINDOW LOOP AND MOUSE SETUP
   // runWindowLevelLoop(window, map, baseCell, enemyList, sfmlLoader);
    return (0);
}
