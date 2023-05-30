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
#include "src/TDPlayer/TDPlayerSave.hpp"
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

int resultOfEndGameActions(TDPlayerSave &playerData, int exitResult, int levelPlayed, int planetPlayed) {
    if (exitResult == -1) {
        std::cout << "Error on game initialisation" << std::endl;
        return (-1);
    }
    else if (exitResult == 1) {
        std::cout << "Player leaved current game" << std::endl;
        return (1);
    }
    else if (exitResult == 2) {
        std::cout << "Player won current game" << std::endl;
        if (planetPlayed == 1 && (playerData.getUnlockedPlanet1() == planetPlayed))
            playerData.unlockPlanet1Level();
        else if (planetPlayed == 2 && (playerData.getUnlockedPlanet2() == planetPlayed))
            playerData.unlockPlanet2Level();
        else if (planetPlayed == 3 && (playerData.getUnlockedPlanet3() == planetPlayed))
            playerData.unlockPlanet3Level();
        return (2);
    }
    else if (exitResult == 3) {
        std::cout << "Player lost current game" << std::endl;
        return (3);
    }
    else {
        std::cout << "Unknow current game exit reason" << std::endl;
        return (0);
    }
}

void displayEndScreen(Menus &menu, int exitResult) {
    if (exitResult <= 1)
        return ;
    else if (exitResult == 2) {
        menu.loadWonScreen();
    }
    else if (exitResult == 3) {
        menu.loadLooseScreen();
    }
}

int launchGame(SFMainSoundPlayer &sfSoundPlayer, TDPlayerSave &playerData, int gameDifficulty, sf::RenderWindow &window, int levelToPlay, int planetToLoad) {

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
    SFTowerSoundLoader sfTowerSoundLoader(playerData.getMusicVolume() / 12, playerData.getSoundVolume());
  //  sfSoundPlayer.stopMenuMusic();

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
    int exitResult = 0;
    try {
        exitResult = currentGame.launch(sfmlLoader, window, playerData.getGlobalVolume());
        return (exitResult);
    } catch (const std::out_of_range& ex) {
        std::cout << "Exception at line : " << __LINE__ << " in file : "<< __FILE__<< " : " << ex.what() << std::endl;
    }
}

int launchMultiplayerGame(SFMainSoundPlayer &sfSoundPlayer, TDPlayerSave &playerData, int gameDifficulty, sf::RenderWindow &window, int levelToPlay, int planetToLoad, NetworkController* networkController) {

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
    SFTowerSoundLoader sfTowerSoundLoader(playerData.getMusicVolume() / 12, playerData.getSoundVolume());
   // sfSoundPlayer.stopMenuMusic();
    
    Game currentGame(gameDifficulty, levelToPlay, playerOne, sfSoundPlayer, sfTowerSoundLoader, networkController, planetToLoad);

    int exitResult;
    try {
        exitResult = currentGame.launch(sfmlLoader, window, playerData.getGlobalVolume());
        return (exitResult);
    } catch (const std::out_of_range& ex) {
        std::cout << "Exception at line : " << __LINE__ << " in file : "<< __FILE__<< " : " << ex.what() << std::endl;
    }
}

int main() {
    // RETRIEVE PLAYER SAVE
    const std::string saveFile = "ressources/playerdata.bin";
    TDPlayerSave playerData(saveFile);
    // PLAYER DATA RETRIEVE DEBUGGING
    playerData.debugDisplayPlayerInfos();
    //
    SFMainSoundLoader mainSoundLoader;
    SFMainSoundPlayer sfSoundPlayer(mainSoundLoader, playerData.getGlobalVolume(), playerData.getMusicVolume() / 12, playerData.getSoundVolume());
    // LAUNCHING MENU
    sfSoundPlayer.playMenuMusic();
    sf::RenderWindow windowTestMenu(sf::VideoMode(1920, 1080), "Space Defender", sf::Style::Default);
    Menus menu(windowTestMenu.getSize().x, windowTestMenu.getSize().y, playerData);
    menu.loadHome();
    sfSoundPlayer.refreshAllMenuVolume(playerData.getGlobalVolume(), playerData.getMusicVolume() / 12, playerData.getSoundVolume());
    // SETTINGS SPACE DEFENDER LOGO
    sf::Image image;
    if (!image.loadFromFile("ressources/Icons/LogoSpaceDefender.png")) {
        std::cout << "Logo didn't load correctly." << std::endl;
    }
    else
        windowTestMenu.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    // FOR LOOP LOGIC
    std::string selectionInformation("none");
    int         levelToPlay = -1;
    int         planetToLoad = -1;
    bool        gameMode = 0;
    bool        isInSettings = false;
    while (windowTestMenu.isOpen()) {
        sf::Event event;
        sfSoundPlayer.checkForMenuMusicToReplay();
        while (windowTestMenu.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                windowTestMenu.close();
            }
            if (isInSettings) {
                if (event.type == sf::Event::MouseButtonReleased)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(windowTestMenu);
                    menu.checkIfVolumeClicked(mousePosition, playerData, saveFile);
                    sfSoundPlayer.refreshAllMenuVolume(playerData.getGlobalVolume(), playerData.getMusicVolume() / 12, playerData.getSoundVolume());
                }
            }
            if (event.type == sf::Event::MouseButtonPressed &&
                sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sfSoundPlayer.playMenuClick();
                playerData.setDifficulty(menu.getDifficulty());
                playerData.savePlayerData(saveFile);
                sf::Vector2i mousePosition = sf::Mouse::getPosition(windowTestMenu);
                std::string clicked = menu.checkForClick(mousePosition);
                if (clicked != "no") {
                    if (clicked == "exit")
                        return (1);
                    else if (clicked.find("settings") != std::string::npos) {
                        isInSettings = true;
                    }
                    else if (clicked.find("resetconfirmed") != std::string::npos) {
                        isInSettings = false;
                        playerData.initPlayerData(saveFile);
                    }
                    else if (clicked.find("ip:") != std::string::npos) {
                        // LAUNCH CONNEXION TO HOST WITH menu.getIp

                        
                        isInSettings = false;
                        std::string ipAddressToConnect = clicked.substr(3);
                        NetworkController* networkController = new NetworkController(false);
                        sf::IpAddress serverAddress(ipAddressToConnect);
                        if(networkController->connectToServer(serverAddress)){
                            std::cout << "connected to server" << std::endl;
                            std::string levelstr = networkController->receiveMessage(networkController->getServerSocket());
                            levelToPlay = atoi(levelstr.c_str());
                            std::cout << "levelToPlay : " << levelToPlay << std::endl;
                            std::string planetstr = networkController->receiveMessage(networkController->getServerSocket());
                            std::cout << "planetstr : " << planetstr << std::endl;
                            planetToLoad = atoi(planetstr.c_str());
                            
                            std::cout << "planetToLoad : " << planetToLoad << std::endl;
                            std::string difficultystr = networkController->receiveMessage(networkController->getServerSocket());
                            int difficulty = atoi(difficultystr.c_str());
                            std::cout << "difficulty : " << difficulty << std::endl;
                            
                            
                            int exitResult = launchMultiplayerGame(sfSoundPlayer, playerData, difficulty, windowTestMenu, levelToPlay, planetToLoad, networkController);
                            resultOfEndGameActions(playerData, exitResult, levelToPlay, planetToLoad);
                            playerData.savePlayerData(saveFile);
                            displayEndScreen(menu, exitResult);
                        }else{
                            std::cout << "failed to connect to server" << std::endl;
                        }
                    }
                    else if (clicked.find("hostwait") != std::string::npos) {
                        isInSettings = false;
                        // LAUNCH HOST WAITING FOR CLIENT
                        std::cout << "hostwait" << std::endl;
                        
                        
                    }
                    else {
                        isInSettings = false;
                        selectionInformation = clicked;
                        levelToPlay = extractLevelNumber(selectionInformation);
                        planetToLoad = extractPlanetNumber(selectionInformation);
                        std::string str1(selectionInformation);
                        gameMode = extractGameMode(str1);
                        if (gameMode == 0) {
                            int exitResult =launchGame(sfSoundPlayer, playerData, menu.getDifficulty(), windowTestMenu, levelToPlay,
                                       planetToLoad);
                            resultOfEndGameActions(playerData, exitResult, levelToPlay, planetToLoad);
                            playerData.savePlayerData(saveFile);
                            displayEndScreen(menu, exitResult);
                        }
                        else {
                            // OPEN WINDOW WITH HOST INFOS AND WAIT
                            sf::IpAddress serverAddress = sf::IpAddress::getLocalAddress();
                            menu.setIp(serverAddress.toString());
                            menu.loadHost(serverAddress.toString());
                            windowTestMenu.clear();
                            menu.drawMenu(windowTestMenu);
                            windowTestMenu.display();
                            NetworkController* networkController = new NetworkController(true);
                            std::cout << "network controller created" << std::endl;

                            levelToPlay = extractLevelNumber(selectionInformation);
                            planetToLoad = extractPlanetNumber(selectionInformation);
                            std::cout << "waiting for connection" << std::endl;
                            std::thread networkThread(&NetworkController::waitForConnection, std::ref(networkController));
                            while (networkController->isWaitingScreen()) {
                                windowTestMenu.clear();
                                menu.drawMenu(windowTestMenu);
                                windowTestMenu.display();
                            }
                            // NEED TO MAKE A SPECIAL BACK BUTTON TO JOIN THREAD AND STOP WAITING
                            networkThread.join();

                            std::cout << "All clients connected, launching game " << std::endl;
                            
                            networkController->sendMessageToAllClients(std::to_string(levelToPlay));
                            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                            networkController->sendMessageToAllClients(std::to_string(planetToLoad));
                            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                            std::cout << "planetToLoad : " << std::to_string(planetToLoad) << std::endl;
                            std::cout << "levelToPlay : " << std::to_string(levelToPlay) << std::endl;
                            std::cout << "difficulty : " << std::to_string(menu.getDifficulty()) << std::endl;
                            networkController->sendMessageToAllClients(std::to_string(menu.getDifficulty()));
                            int exitResult = launchMultiplayerGame(sfSoundPlayer, playerData, menu.getDifficulty(), windowTestMenu, levelToPlay, planetToLoad, networkController);
                            resultOfEndGameActions(playerData, exitResult, levelToPlay, planetToLoad);
                            playerData.savePlayerData(saveFile);
                            displayEndScreen(menu, exitResult);

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
