#include "SFMLHud.hpp"
#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
SFMLHud::SFMLHud(SFMLLoader *sfmlLoader, sf::RenderWindow *window, int gamePosX, int gamePosY, int lifeNumber, int waveNumber, int money, int maxWaveNumber, int level) {
    
    _lifeNumber = lifeNumber;
    _waveNumber = waveNumber;
    _maxWaveNumber = maxWaveNumber;
    _money = money;
    _level = level;
    this->isPaused = false;
    this->selectedTower = nullptr;
    towerStoreList = std::vector<std::vector<Tower*>>();
    this->_window = window;
    this->mainFont.loadFromFile("Fonts/neuropol.otf");
    this->m_lifeText.setFont(this->mainFont);
    this->m_lifeText.setCharacterSize(32);
    this->m_waveText.setFont(this->mainFont);
    this->m_waveText.setCharacterSize(28);
    this->m_moneyText.setFont(this->mainFont);
    this->m_moneyText.setCharacterSize(28);
    this->setMessage("Build a tower to kill the enemies !");
    textMessage.setFont(mainFont);
    if (!m_backgroundTexture.loadFromFile("Sprites/hud_background.png")) {
        std::cout << "Error on loading texture..." << std::endl;
    }
    if (!heartTexture.loadFromFile("Sprites/heart.png")) {
        std::cout << "Error on loading texture..." << std::endl;
    }
    if (!coinTexture.loadFromFile("Sprites/coin.png")) {
        std::cout << "Error on loading texture..." << std::endl;
    }
    if (!removeTexture.loadFromFile("Sprites/remove.png")) {
        std::cout << "Error on loading texture..." << std::endl;
    }
    if (!wallTexture.loadFromFile("Sprites/wall.png")) {
        std::cout << "Error on loading texture..." << std::endl;
    }
    if(!pauseButtonTexture.loadFromFile("Sprites/Buttons/play.png")){
        std::cout << "Error on loading texture..." << std::endl;
    }
    if(!volumeButtonTexture.loadFromFile("Sprites/Buttons/volume.png")){
        std::cout << "Error on loading texture..." << std::endl;
    }
    if(!homeButtonTexture.loadFromFile("Sprites/Buttons/home.png")){
        std::cout << "Error on loading texture..." << std::endl;
    }
    
    volumeButtonSprite.setTexture(volumeButtonTexture);
    volumeButtonSprite.setPosition(605, 400);
    pauseButtonSprite.setTexture(pauseButtonTexture);
    pauseButtonSprite.setPosition(855, 400);
    homeButtonSprite.setTexture(homeButtonTexture);
    homeButtonSprite.setPosition(1105, 400);
    

    coinSprite.setTexture(coinTexture);
    coinSprite.setPosition(50, 150);
    m_levelText.setFont(mainFont);
    m_levelText.setCharacterSize(28);
    m_levelText.setString("Level " + std::to_string(_level));
    m_levelText.setPosition(150, 5);
    removeSprite.setTexture(removeTexture);
    removeSprite.setScale(2,2);
    removeSprite.setPosition(1550, 875);
    removeRect.setSize(sf::Vector2f(100, 100));
    removeRect.setPosition(1550, 875);
    removeRect.setFillColor(sf::Color::Transparent);
    removeRect.setOutlineThickness(2);
    removeRect.setOutlineColor(sf::Color::White);
    wallSprite.setTexture(wallTexture);
    wallSprite.setPosition(1650, 900);
    wallSprite.setScale(1.5,1.5);
    wallRect.setSize(sf::Vector2f(60, 60));
    wallRect.setPosition(1655, 905);
    wallRect.setFillColor(sf::Color::Transparent);
    wallRect.setOutlineThickness(3);
    wallRect.setOutlineColor(sf::Color::Black);
    wallPriceText.setFont(mainFont);
    wallPriceText.setColor(sf::Color::Black);
    wallPriceText.setCharacterSize(28);
    wallPriceText.setString("5 coins");
    wallPriceText.setPosition(1725, 915);
    /*
    wallPriceImage.setTexture(coinTexture);
    wallPriceImage.setPosition(385, 940);
    wallPriceImage.setScale(0.30, 0.30);
    */


    
    
    
    
}

void SFMLHud::update() {
    m_waveText.setString("Wave: " + std::to_string(_waveNumber) + "/" + std::to_string(_maxWaveNumber));
    m_moneyText.setString(std::to_string(_money));
    
}

void SFMLHud::draw() {
    // Dessiner la texture du fond en répétition verticale
    
    // Afficher un sprite de coeur pour chaque vie restante
    int windowHeight = _window->getSize().y;
    int textureHeight = m_backgroundTexture.getSize().y;
    for (int y = 0; y < windowHeight; y += textureHeight) {
        sf::Sprite sprite1(m_backgroundTexture);
        sprite1.setPosition(0, y);
        _window->draw(sprite1);
        sf::Sprite sprite2(m_backgroundTexture);
        sprite2.setPosition(m_backgroundTexture.getSize().x, y);
        _window->draw(sprite2);
        sf::Sprite sprite3(m_backgroundTexture);
        sprite3.setPosition(m_backgroundTexture.getSize().x *2, y);
        _window->draw(sprite3);
        sf::Sprite sprite4(m_backgroundTexture);
        sprite4.setPosition(m_backgroundTexture.getSize().x *3, y);
        _window->draw(sprite4);
        sf::Sprite sprite5(m_backgroundTexture);
        sprite5.setPosition(1450, y);
        _window->draw(sprite5);
        sf::Sprite sprite6(m_backgroundTexture);
        sprite6.setPosition(m_backgroundTexture.getSize().x + 1450, y);
        _window->draw(sprite6);
        sf::Sprite sprite7(m_backgroundTexture);
        sprite7.setPosition(m_backgroundTexture.getSize().x *2 + 1450, y);
        _window->draw(sprite7);
        sf::Sprite sprite8(m_backgroundTexture);
        sprite8.setPosition(m_backgroundTexture.getSize().x *3 + 1450, y);
        _window->draw(sprite8);
    }
    _window->draw(m_levelText);
    int heartSize = 32;
    int heartSpacing = 10;
    
    for (int i = 0; i < _lifeNumber; i++) {
        sf::Sprite heartSprite(heartTexture);
        heartSprite.setPosition(50 + (heartSize + heartSpacing) * i, 50);
        _window->draw(heartSprite);
    }
    
    _window->draw(coinSprite);
    m_moneyText.setPosition(150, 175);
    _window->draw(m_moneyText);
    m_waveText.setPosition(50, 100);
    _window->draw(m_waveText);

    textMessage.setPosition(15, 300);
    
    textMessage.setColor(sf::Color::Black);
    textMessage.setCharacterSize(16);
    
    _window->draw(textMessage);
    if(selectedTower == nullptr){
        int towerInfoX = 1535;
        int towerInfoY = 50;

        if (towerStoreList.empty()) {
            std::cout << "towerStoreList is empty" << std::endl;
        }
        for (std::size_t i = 0; i < towerStoreList.size(); ++i) {
        
        sf::Text towerNameText;
        towerNameText.setFont(mainFont);
        towerNameText.setCharacterSize(24);
        towerNameText.setPosition(towerInfoX, towerInfoY);
        towerNameText.setString(towerStoreList[i].at(0)->getTowerName());
        _window->draw(towerNameText);

        // Afficher le coût de la tour
        sf::Text towerCostText;
        towerCostText.setFont(mainFont);
        towerCostText.setCharacterSize(18);
        towerCostText.setPosition(towerInfoX, towerInfoY + 30);
        towerCostText.setString("Cost: " + std::to_string(towerStoreList[i].at(0)->getCost()) + " coins");
        _window->draw(towerCostText);

        // Afficher le sprite de la tour
        sf::Sprite towerSprite = towerStoreList[i].at(0)->getTowerSprite();
        towerSprite.setPosition(towerInfoX - 25, towerInfoY + 30);
        sf::RectangleShape towerInfoRect(sf::Vector2f(400, 80));
        towerInfoRect.setPosition(towerInfoX - 50, towerInfoY - 15);
        towerInfoRect.setFillColor(sf::Color::Transparent);
        towerInfoRect.setOutlineThickness(2);
        towerInfoRect.setOutlineColor(sf::Color::White);
        _window->draw(towerInfoRect);
        _window->draw(towerSprite);

        towerInfoY += 100; // Avancer la position Y pour la prochaine tour
        }
        
        _window->draw(wallSprite);
        _window->draw(wallRect);
        _window->draw(wallPriceText);
    }else{
        sf::Text towerNameText;
        towerNameText.setFont(mainFont);
        towerNameText.setCharacterSize(24);
        towerNameText.setPosition(1600, 25);
        towerNameText.setString(selectedTower->getTowerName());
        _window->draw(towerNameText);

        //tower selected info Menu - upgrade, sell buttons
        sf::Sprite towerSprite = selectedTower->getTowerSprite();
        towerSprite.setPosition(1700, 150);
        towerSprite.setScale(1.5, 1.5);
        
        sf::Text towerLevelText;
        
        if(selectedTower->isMaxed()){
            towerLevelText.setString("Level: " + std::to_string(selectedTower->getLevel() + 1) + " (Max)");
        }else{
            towerLevelText.setString("Level: " + std::to_string(selectedTower->getLevel() + 1) + " -> " + std::to_string(selectedTower->getLevel() + 2) );
        }
        
        towerLevelText.setFont(mainFont);
        
        towerLevelText.setCharacterSize(24);
        towerLevelText.setPosition(1465, 250);
        
        _window->draw(towerLevelText);

        sf::Text towerDamage;
        towerDamage.setFont(mainFont);
        towerDamage.setCharacterSize(24);
        towerDamage.setPosition(1465, 300);
        if(!selectedTower->isMaxed()){
            
            towerDamage.setString("Damage: " + std::to_string(selectedTower->getDamage()) + " -> " + std::to_string(selectedTower->getUpgradeDamage()));
        }else{
            towerDamage.setString("Damage: " + std::to_string(selectedTower->getDamage()));
        }
        _window->draw(towerDamage);
        sf::Text towerRange;
        towerRange.setFont(mainFont);
        towerRange.setCharacterSize(24);
        towerRange.setPosition(1465, 350);
        towerRange.setString("Range: " + std::to_string(selectedTower->getRange()));
        _window->draw(towerRange);
        sf::Text towerSpeed;
        towerSpeed.setFont(mainFont);
        towerSpeed.setCharacterSize(24);
        towerSpeed.setPosition(1465, 400);
        std::stringstream stream;
        stream << std::fixed << std::setprecision(1) << 1000/(selectedTower->getTimeBetweenAttack()*1000);
        std::string str = stream.str();
        towerSpeed.setString("Attack Speed: " + str);
        
        _window->draw(towerSpeed);
        
        if(!selectedTower->isMaxed()){
            upgradeRect.setSize(sf::Vector2f(190, 70));
            upgradeRect.setPosition(1585, 495);
            upgradeRect.setFillColor(sf::Color::Transparent);
            upgradeRect.setOutlineThickness(3);
            upgradeRect.setOutlineColor(sf::Color::White);
            sf::Text towerUpgradeCost;
            towerUpgradeCost.setString("UPGRADE \n" + std::to_string(selectedTower->getUpgradeCost()) + " coins");
            towerUpgradeCost.setFont(mainFont);
            towerUpgradeCost.setColor(sf::Color::Yellow);
            towerUpgradeCost.setCharacterSize(24);
            towerUpgradeCost.setPosition(1600, 500);
            _window->draw(upgradeRect);
            _window->draw(towerUpgradeCost);
            
        }
        sellRect.setSize(sf::Vector2f(190, 70));
        sellRect.setPosition(1585, 595);
        sellRect.setFillColor(sf::Color::Transparent);
        sellRect.setOutlineThickness(3);
        sellRect.setOutlineColor(sf::Color::White);
        sf::Text towerSellCost;
        towerSellCost.setString("    SELL \n" + std::to_string(selectedTower->getCost()/2) + " coins");
        towerSellCost.setFont(mainFont);
        towerSellCost.setColor(sf::Color::Red);
        towerSellCost.setCharacterSize(24);
        towerSellCost.setPosition(1600, 600);
        _window->draw(sellRect);
        _window->draw(towerSellCost);
        
       




        
        _window->draw(towerSprite);

    }
    if(this->isPaused){
        
        sf::RectangleShape blurRect(sf::Vector2f(_window->getSize().x, _window->getSize().y));
        blurRect.setFillColor(sf::Color(0, 0, 0, 175));
        _window->draw(blurRect);

        sf::Texture texture;
        texture.create(_window->getSize().x, _window->getSize().y);
        texture.update(*_window);
        sf::Sprite sprite(texture);
        sprite.setPosition(0, 0);
        
        
        _window->draw(homeButtonSprite);
        _window->draw(volumeButtonSprite);
        _window->draw(pauseButtonSprite);
    
   }
}
