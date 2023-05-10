#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <mutex>
#include <cstdlib>

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
#include "src/TDGame/NetworkController.hpp"
#include "src/TDGame/Menus.hpp"

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

int extractPlanetNumber(const std::string& str) {
    size_t planetPos = str.find("planet");
    if (planetPos != std::string::npos) {
        std::string planetNumberStr = str.substr(planetPos + 6);
        return std::atoi(planetNumberStr.c_str());
    }
    return (-1);
}

int extractLevelNumber(const std::string& str) {
    size_t levelPos = str.find("level");
    if (levelPos != std::string::npos) {
        // Extract the number following "level"
        std::string levelNumberStr = str.substr(levelPos + 5);
        return std::atoi(levelNumberStr.c_str());
    }
    return (-1);
}

void launchGame(SFMainSoundPlayer &sfSoundPlayer, int musicVolume, int soundVolume, int gameDifficulty, sf::RenderWindow &window) {
    // SETTING WINDOW AND MAP
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    window.setActive(true);
    SFMLLoader sfmlLoader;
    // CREATE GAME OBJET
    TDPlayer *playerOne = new TDPlayer("Joueur1");
    SFTowerSoundLoader sfTowerSoundLoader(musicVolume / 12, soundVolume);
    sfSoundPlayer.playGameMusic1();
    /*  NetworkController* networkController = new NetworkController(false);

       if (networkController->getIsServer() == true) {
            std::string message = "5";
            networkController->sendMessageToAllClients(message);
        } else {
            std::string message = networkController->receiveMessage(networkController->getServerSocket());
            std::cout << "Message received : " << message << std::endl;
        }*/

    Game currentGame(gameDifficulty, 1, playerOne, sfSoundPlayer, sfTowerSoundLoader, nullptr);
    try {
        if (currentGame.launch(sfmlLoader, window) == -1) {
            std::cout << "Error on map initialisation" << std::endl;
            return ;
        }
    } catch (const std::out_of_range& ex) {
        std::cout << "Exception at line : " << __LINE__ << " in file : "<< __FILE__<< " : " << ex.what() << std::endl;
    }
    // WINDOW LOOP AND MOUSE SETUP
    // runWindowLevelLoop(window, map, baseCell, enemyList, sfmlLoader);
}

int main() {
    // SETTING SOUNDS
    int musicVolume = 100;
    int soundVolume = 100;
    int globalVolume = 50;
    SFMainSoundLoader mainSoundLoader;
    SFMainSoundPlayer sfSoundPlayer(mainSoundLoader, globalVolume, musicVolume / 12, soundVolume);
    // LAUNCHING MENU
    sfSoundPlayer.playMenuMusic();
    sf::RenderWindow windowTestMenu(sf::VideoMode(1920, 1080), "SFML Window", sf::Style::Default);
    Menus menu(windowTestMenu.getSize().x, windowTestMenu.getSize().y);
    menu.loadHome();
    std::string selectionInformation("none");
    int         levelToPlay = -1;
    int         planetToLoad = -1;
    int gameDifficulty = 1; // SETTINGS DEFAULT DIFFICULTY
    while (windowTestMenu.isOpen()) {
        sf::Event event;
        while (windowTestMenu.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                windowTestMenu.close();
            }
            if (event.type == sf::Event::MouseButtonPressed &&
                sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(windowTestMenu);
                std::string clicked = menu.checkForClick(mousePos);
                if (clicked != "no") {
                    if (clicked == "exit")
                        return (1);
                    else {
                        selectionInformation = clicked;
                        levelToPlay = extractLevelNumber(selectionInformation);
                        planetToLoad = extractPlanetNumber(selectionInformation);
                        launchGame(sfSoundPlayer, musicVolume, soundVolume, gameDifficulty, windowTestMenu);
                    }
                }
            }
        }
        windowTestMenu.clear();
        // ADD LOOP LOGIC HERE
        menu.drawMenu(windowTestMenu);
        windowTestMenu.display();
    }
    sfSoundPlayer.stopMenuMusic();
    //OLD GAME LAUNCH HERE
    return (0);
}
