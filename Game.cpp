#include <unistd.h>
#include <string>
#include "Game.hpp"

Game::Game(int difficulty, int level){
    this->levelRetriever = new RetrieveLevel(level);
    this->difficulty = difficulty;
    this->baseCoord = {0,0};
    this->lifeNumber = 15/(difficulty);
    this->currentWaveNumber = 0;
    std::vector<MapCell> spawnCells;
//    this->towerList = new std::vector<Tower *>();
    this->enemyList = this->levelRetriever->getNextLevel();
    this->coinNumber = 500-(difficulty*100);
}

void Game::loop(){
    // GAME INITIALISATON

    while(true){
        startLevel();
        while(!this->gameEnd()){
            //* Run while game isnt ended
            for(int i = 0; i<= this->enemyList.size();i++){
                //* for each wave
                //* start wave
                this->startWave();
                while(!this->waveEnd()){
                    //* While all ennemies of the current wave arent dead
                    //* if an enemy is at the base decrease life number
                    enemyAtBase();
                }
                //* end wave
            }
        } 
    }
}

void Game::display(){
    //* Display/Actualize map   
/*    while (SFWindow.isOpen()) {
        SFWindow.clear();
        for (int i = 0; i<= spriteList.size(); i++) {
            SFWindow.draw(spriteList[i]);
        }
    SFWindow.display();
    }*/
}

bool Game::waveEnd(){
    //* return true if the current wave is ended , ifnot return else
    if(this->enemyList[this->currentWaveNumber].size() == 0){
        //* if all the ennemies from the current wave are dead == wave ended
        std::cout << "wave ended" << std::endl;
        //* deactivate towers, increase wave number
        this->deactivateTowers();
        this->currentWaveNumber++;
        return true;
    }else{
        //* if all the ennemies from the current wave aren't dead == wave not ended
        return false;
    }
}

bool Game::gameEnd(){
    //* return true if game is ended, ifnot false
    
    if(this->lifeNumber == 0){
        std::cout << "ending game" << std::endl;
        //* if player lost all his lifes = game lost
        this->deactivateTowers();
        this->gameLost();
        return true;
    }else if(this->enemyList[this->enemyList.size()-1].size() == 0){
        std::cout << "ending level" << std::endl;
        //* if all enemies form the last wave are dead  = game won
        this->deactivateTowers();
        this->gameWon();
        return true;
    }else{
        return false;
    }
}

void Game::gameWon(){
    //* game won
    std::cout << "Game Won !!!" << std::endl;    
}

void Game::gameLost(){
    //* game lost
    std::cout << "Game Lost !!!" << std::endl;
}

void Game::startWave(){
    //* start the wave 
    std::cout << "Starting wave" << currentWaveNumber << "/" << this->enemyList.size() << std::endl;
    std::cout << "The wave contains " <<  this->enemyList[this->currentWaveNumber].size() << " enemies" << std::endl;
    std::cout << "Life number : " << this->lifeNumber << std::endl;
    std::cout << "Coin number : " << this->coinNumber << std::endl;
     
    //* activate towers
    this->activateTowers();
    for(int j = 0; j <= this->enemyList[this->currentWaveNumber].size();j++ ){
        //* Set the positions of all enemies to their spawn
        std::cout << "Spawning enemies" << std::endl;
        if(this->enemyList[this->currentWaveNumber][j] != nullptr){
//            this->enemyList[this->currentWaveNumber][j]->setPosX(spawnCells[j%spawnCells.size()].posX)
  //          this->enemyList[this->currentWaveNumber][j]->setPosY(spawnCells[j%spawnCells.size()].posY);
            //* Activate the enemy loop
            this->enemyList[this->currentWaveNumber][j]->run();
            //* wait time between enemy spawn
            sleep(3000);
        }
    }
}

void Game::activateTowers(){
    //* Activate all towers
    std::cout << "Tower activation" << std::endl;
    for(int i = 0; i<= this->towerList.size(); i++ ){
        this->towerList[i]->run(this->enemyList[this->currentWaveNumber]);
    }
}

void Game::deactivateTowers(){
    //* deactivate all towers
    std::cout << "Tower deactivation" << std::endl;
    for(int i = 0; i<= this->towerList.size(); i++ ){
        this->towerList[i]->deactivate();
    }
}

bool Game::enemyAtBase(){
    //* test if an enemy is at the base
    for(int i = 0; i<= this->enemyList[this->currentWaveNumber].size(); i++ ){
        //* if an enemy is at the base -> decrease life number and erase the enemy
        std::cout << "An enemy is a the base" << std::endl;
        if(this->enemyList[this->currentWaveNumber][i]->getPosX() == this->baseCoord.x && this->enemyList[this->currentWaveNumber][i]->getPosY() == this->baseCoord.y){
            this->lifeNumber--;
            std::cout << "life number :" << this->lifeNumber << std::endl;
            this->enemyList[this->currentWaveNumber].erase(std::remove(enemyList[this->currentWaveNumber].begin(), enemyList[this->currentWaveNumber].end(), enemyList[this->currentWaveNumber][i]), enemyList[this->currentWaveNumber].end());
            return true;
        }else{
            return false;
        }
    }
}

void Game::createTower(){
    //* Tower choice
    std::cout << "Enter the integer corresponding to the type of tower you want to build :" << std::endl;
    std::cout << "1/ Basic Tower" << std::endl;
    std::cout << "2/ Sniper Tower" << std::endl;
    std::cout << "3/ Anti Air Tower" << std::endl;
    std::cout << "4/ Splash Tower" << std::endl;
    std::cout << "5/ Slow Tower" << std::endl;
    std::cout << "6/ Attack Speed Tower" << std::endl;
    std::string towerType;
    std::getline(std::cin, towerType);
    Tower *newTower;
    switch(stoi(towerType)){
        case 1:
            newTower = new Tower(this);
            break;
        case 2:
          //  SniperTower newTower = new SniperTower(this);
            break;
        case 3:
            //AntiAirTower newTower = new AntiAirTower(this);
            break;
        case 4:
           // SplashTower newTower = new SplashTower(this);
            break;
        case 5:
            //SlowTower newTower = new SlowTower(this);
            break;
        case 6:
            //AttackSpeedTower newTower = new AttackSpeedTower(this, this->towerList);
            break;
        default:
            break;
    }
    if(canBuy(*newTower, 0)){
        //* test if the player has enough coin to buy the tower
        //* ask tower coord
        std::cout << "posX : " << std::endl;
        std::string newTowerPosX;
        std::getline(std::cin, newTowerPosX);
        std::cout << "posY : " << std::endl;
        std::string newTowerPosY;
        std::getline(std::cin, newTowerPosY);  
        if(canPlace(*newTower, stoi(newTowerPosX), stoi(newTowerPosY))){
            newTower->setPosition(stoi(newTowerPosX), stoi(newTowerPosY));
            this->addCoins(0-newTower->getCost(0));
            this->towerList.push_back(newTower);
            newTower->run(this->enemyList[this->currentWaveNumber]);
            std::cout << "Tower succesfully created " << std::endl;
            std::cout << "coin number : " << this->coinNumber << std::endl;
        }else{
            std::cout << "Coords not valid " << std::endl;
        }
    }else{
        delete newTower;
    }
}

bool Game::canBuy(Tower &tower, int level){
    //* test if the player has enough coin to buy the tower
    if(this->coinNumber >= tower.getCost(level)){
        std::cout << "You have enough coins !" << std::endl;
        return true;
    }else{
        std::cout << "You don't have enough coins !" << std::endl;
        return false;
    }
}

bool Game::canPlace(Tower &tower, int xPos, int yPos){
    //* detect if the tower can be placed at theses coords
    for(int i = 0; i<= this->towerList.size(); i++){
        if(xPos >= towerList[i]->getPosition().x && xPos >= towerList[i]->getPosition().y && xPos < towerList[i]->getPosition().x + tower.getSize().x && yPos < towerList[i]->getPosition().y + tower.getSize().y){
            return false;
        }
    }
    return true;
}

void Game::addCoins(int number){
    this->coinNumber+= number;
    std::cout << "You know have " << this->coinNumber << " coins" << std::endl;
}

void Game::upgradeTower(Tower &tower){
    if(!tower.isMaxed()){
        if(canBuy(tower, tower.getLevel() + 1)){
            this->addCoins(0-tower.getCost(tower.getLevel() + 1));
            tower.upgrade();      
        }
    }
}

void Game::startLevel(){
    std::cout << "Starting level ..." << std::endl;
    //* start level
    //*this->enemyList = retrieveLevel.getNextLevel();
}