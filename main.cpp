#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <mutex>
#include <cstdlib>

#include "src/TDGraphics/SFMLLoader.hpp"
#include "src/TDGraphics/SFMLLoaderPlanet1.hpp"
#include "src/TDGraphics/SFMLLoaderPlanet2.hpp"
#include "src/TDGraphics/SFMLLoaderPlanet3.hpp"
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
#include "src/TDGame/NetworkController.hpp"


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

bool extractGameMode(const std::string& infoString) {
    size_t singlePos = infoString.find("single");
    size_t multiPos = infoString.find("multi");
    if (singlePos != std::string::npos) {
        return (0);
    }
    else if (multiPos != std::string::npos) {
        return (1);
    }
    else
        return (0);
}

void launchGame(SFMainSoundPlayer &sfSoundPlayer, int musicVolume, int soundVolume, int globalVolume, int gameDifficulty, sf::RenderWindow &window, int levelToPlay, int planetToLoad) {

    // SETTING WINDOW AND MAP
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    window.setActive(true);
    SFMLLoader sfmlLoader;

    if (planetToLoad == 1) {
        SFMLLoaderPlanet1 sfmlLoader1;
        sfmlLoader = sfmlLoader1;
    }
    else if (planetToLoad == 2) {
        SFMLLoaderPlanet2 sfmlLoader2;
        sfmlLoader = sfmlLoader2;
    }
    else if (planetToLoad == 3) {
        SFMLLoaderPlanet3 sfmlLoader3;
        sfmlLoader = sfmlLoader3;
    }
    else {
        SFMLLoaderPlanet1 sfmlLoader1;
        sfmlLoader = sfmlLoader1;
    }


    // CREATE GAME OBJET
    TDPlayer *playerOne = new TDPlayer("Joueur1");
    SFTowerSoundLoader sfTowerSoundLoader(musicVolume / 12, soundVolume);
    sfSoundPlayer.stopMenuMusic();
    sfSoundPlayer.playGameMusic1();
    
    //NetworkController* networkController = new NetworkController(false); // commenter pour tester solo
    /*if(networkController != nullptr){
      if (networkController->getIsServer() == true) {
          std::string levelstr = "1";
          networkController->sendMessageToAllClients(levelstr);
          level = atoi(levelstr.c_str());

      } else {
          std::string levelstr = networkController->receiveMessage(networkController->getServerSocket());
          level = atoi(levelstr.c_str());
      }
    }*/
    Game currentGame(gameDifficulty, levelToPlay, playerOne, sfSoundPlayer, sfTowerSoundLoader, nullptr, planetToLoad);

    try {
        if (currentGame.launch(sfmlLoader, window, globalVolume) == -1) {
            std::cout << "Error on map initialisation" << std::endl;
            return ;
        }
    } catch (const std::out_of_range& ex) {
        std::cout << "Exception at line : " << __LINE__ << " in file : "<< __FILE__<< " : " << ex.what() << std::endl;
    }
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
    Menus menu(windowTestMenu.getSize().x, windowTestMenu.getSize().y, globalVolume, musicVolume, soundVolume);
    menu.loadHome();
    std::string selectionInformation("none");
    int         levelToPlay = -1;
    int         planetToLoad = -1;
    bool        gameMode = 0;
    int         gameDifficulty = 1; // SETTINGS DEFAULT DIFFICULTY
    bool        isInSettings = false;
    while (windowTestMenu.isOpen()) {
        sf::Event event;
        while (windowTestMenu.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                windowTestMenu.close();
            }
            if (isInSettings) {
                if (event.type == sf::Event::MouseButtonReleased)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(windowTestMenu);
                    menu.checkIfVolumeClicked(mousePosition, &globalVolume, &musicVolume, &soundVolume);
                    sfSoundPlayer.refreshAllMenuVolume(globalVolume, musicVolume, soundVolume);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed &&
                sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(windowTestMenu);
                std::string clicked = menu.checkForClick(mousePosition);
                if (clicked != "no") {
                    if (clicked == "exit")
                        return (1);
                    else if (clicked.find("settings") != std::string::npos) {
                        isInSettings = true;
                    }
                    else if (clicked.find("ip:") != std::string::npos) {
                        // LAUNCH CONNEXION TO HOST WITH menu.getIp
                        isInSettings = false;
                        std::string ipAddressToConnect = clicked.substr(3);
                    }
                    else if (clicked.find("hostwait") != std::string::npos) {
                        isInSettings = false;
                        // LAUNCH HOST WAITING FOR CLIENT
                    }
                    else {
                        isInSettings = false;
                        selectionInformation = clicked;
                        levelToPlay = extractLevelNumber(selectionInformation);
                        planetToLoad = extractPlanetNumber(selectionInformation);
                        std::string str1(selectionInformation);
                        gameMode = extractGameMode(str1);
                        if (gameMode == 0)
                            launchGame(sfSoundPlayer, musicVolume, soundVolume, menu.getGlobalVolume(), gameDifficulty, windowTestMenu, levelToPlay, planetToLoad);
                        else {
                            // OPEN WINDOW WITH HOST INFOS AND WAIT
                            menu.loadHost();
                            // WAIT FOR CONNECTION
                        }
                    }
                }
            }
            if ((event.type == sf::Event::TextEntered) && (menu.isIpEntering())) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == '\b' && !menu.getIpAddressField().empty()) { // SUPPRESION CHARACTERE
                        std::string inputString = menu.getIpAddressField();
                        inputString.pop_back();
                        menu.setIpAddressField(inputString);
                    }
                    else if ((menu.getIpAddressField().size() < 15) && (event.text.unicode != '\r')) { // AJOUT DE TEXTE
                        std::string inputString = menu.getIpAddressField();
                        inputString += static_cast<char>(event.text.unicode);
                        menu.setIpAddressField(inputString);
                        menu.loadJoin();
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
