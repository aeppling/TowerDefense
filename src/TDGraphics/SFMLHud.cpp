#include "SFMLHud.hpp"
#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
SFMLHud::SFMLHud(SFMLLoader *sfmlLoader, sf::RenderWindow *window, int gamePosX, int gamePosY, int lifeNumber, int waveNumber, int money, int maxWaveNumber, int level) {
    this->gameInfoOffset = 25;
    this->towerSelectorOffset = 50;
    _lifeNumber = lifeNumber;
    _waveNumber = waveNumber;
    _maxWaveNumber = maxWaveNumber;
    _money = money;
    _level = level;
    this->isPaused = false;
    this->selectedTower = nullptr;
    towerStoreList = std::vector<std::vector<Tower*>>();
    this->_window = window;
    this->mainFont.loadFromFile("ressources/Fonts/neuropol.otf");
    this->m_lifeText.setFont(this->mainFont);
    this->m_lifeText.setCharacterSize(32);
    this->m_waveText.setFont(this->mainFont);
    this->m_waveText.setCharacterSize(24);
    this->m_moneyText.setFont(this->mainFont);
    this->m_moneyText.setCharacterSize(30);
    this->setMessage("Build a tower to kill the enemies !");
    textMessage.setFont(mainFont);
    if (!m_backgroundTexture.loadFromFile("ressources/Sprites/Backgrounds/stars_texture.png")) {
        std::cout << "Error on loading texture..." << std::endl;
    }
    if (!heartTexture.loadFromFile("ressources/Sprites/Hud/heart.png")) {
        std::cout << "Error on loading texture..." << std::endl;
    }
    if (!coinTexture.loadFromFile("ressources/Sprites/Hud/coin.png")) {
        std::cout << "Error on loading texture..." << std::endl;
    }
    if (!removeTexture.loadFromFile("ressources/Sprites/Hud/remove.png")) {
        std::cout << "Error on loading texture..." << std::endl;
    }
    if (!wallTexture.loadFromFile("ressources/Sprites/Hud/wall.png")) {
        std::cout << "Error on loading texture..." << std::endl;
    }
    if(!pauseButtonTexture.loadFromFile("ressources/Sprites/Buttons/play.png")){
        std::cout << "Error on loading texture..." << std::endl;
    }
    if(!volumeButtonTexture.loadFromFile("ressources/Sprites/Buttons/volume.png")){
        std::cout << "Error on loading texture..." << std::endl;
    }
    if(!homeButtonTexture.loadFromFile("ressources/Sprites/Buttons/home.png")){
        std::cout << "Error on loading texture..." << std::endl;
    }

    sf::Color fillColor(0,0,0, 140);
    sf::Color outlineColor(0,255,255, 140);

    this->levelTitleContainer.setSize(sf::Vector2f(500, 200));
    this->levelTitleContainer.setPosition(30, 25 + this->gameInfoOffset);
    this->levelTitleContainer.setFillColor(fillColor);
    this->levelTitleContainer.setOutlineThickness(2);
    this->levelTitleContainer.setOutlineColor(outlineColor);

    this->gameInfoContainer.setSize(sf::Vector2f(500, 600));
    this->gameInfoContainer.setPosition(30, 225 + this->gameInfoOffset);
    this->gameInfoContainer.setFillColor(fillColor);
    this->gameInfoContainer.setOutlineThickness(2);
    this->gameInfoContainer.setOutlineColor(outlineColor);

    volumeButtonSprite.setTexture(volumeButtonTexture);
    volumeButtonSprite.setPosition(605, 400);
    pauseButtonSprite.setTexture(pauseButtonTexture);
    pauseButtonSprite.setPosition(855, 400);
    homeButtonSprite.setTexture(homeButtonTexture);
    homeButtonSprite.setPosition(1105, 400);
    

    coinSprite.setTexture(coinTexture);
    coinSprite.setPosition(70, 265 + this->gameInfoOffset);
    m_levelText.setFont(mainFont);
    m_levelText.setCharacterSize(56);
    m_levelText.setString("- Level " + std::to_string(_level) + " -");
    m_levelText.setPosition(95, 65 + this->gameInfoOffset);
    removeSprite.setTexture(removeTexture);
    removeSprite.setScale(2,2);
    removeSprite.setPosition(1550, 875);
    removeRect.setSize(sf::Vector2f(100, 100));
    removeRect.setPosition(1550, 875);
    removeRect.setFillColor(sf::Color::Transparent);
    removeRect.setOutlineThickness(2);
    removeRect.setOutlineColor(sf::Color::White);
    wallSprite.setTexture(wallTexture);
    wallSprite.setPosition(1400, 900);
    wallSprite.setScale(1.3,1.3);
    wallRect.setSize(sf::Vector2f(500, 80));
    wallRect.setPosition(1387, 890);
    wallRect.setFillColor(fillColor);
    wallRect.setOutlineThickness(1);
    sf::Color outlineColorWall(255 ,255,255, 210);
    wallRect.setOutlineColor(sf::Color::White);
    wallPriceText.setFont(mainFont);
    wallPriceText.setColor(sf::Color::White);
    wallPriceText.setCharacterSize(26);
    wallPriceText.setString("BUILD WALL : 5 coins");
    wallPriceText.setPosition(1480, 915);
    /*
    wallPriceImage.setTexture(coinTexture);
    wallPriceImage.setPosition(385, 940);
    wallPriceImage.setScale(0.30, 0.30);
    */  
}

int SFMLHud::checkForPausedClick(sf::RenderWindow &window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (this->volumeButtonSprite.getGlobalBounds().contains(mousePos.x + _GAME_POSITION_X, mousePos.y + _GAME_POSITION_Y)) {
        return (1);
    }
    else if (this->pauseButtonSprite.getGlobalBounds().contains(mousePos.x + _GAME_POSITION_X, mousePos.y + _GAME_POSITION_Y)) {
            return (2);
    }
    else if (this->homeButtonSprite.getGlobalBounds().contains(mousePos.x + _GAME_POSITION_X, mousePos.y + _GAME_POSITION_Y)) {
        return (3);
    }
    return (-1);
}

int SFMLHud::checkForClick(sf::RenderWindow &window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int i = 0;
    while (i < this->towerRectangles.size()) {
        sf::RectangleShape towerCase = towerRectangles.at(i);
        if (towerCase.getGlobalBounds().contains(mousePos.x + _GAME_POSITION_X, mousePos.y + _GAME_POSITION_Y)) {
            return (i);
        }
        i++;
    }
    if (this->wallRect.getGlobalBounds().contains(mousePos.x + _GAME_POSITION_X, mousePos.y + _GAME_POSITION_Y)) {
        return (-2);
    }
    return (-1);
}

int SFMLHud::checkForSellUpgradeClick(sf::RenderWindow &window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (this->sellRect.getGlobalBounds().contains(mousePos.x + _GAME_POSITION_X, mousePos.y + _GAME_POSITION_Y)) {
        return (1);
    }
    else if (this->upgradeRect.getGlobalBounds().contains(mousePos.x + _GAME_POSITION_X, mousePos.y + _GAME_POSITION_Y)) {
        return (2);
    }
    else if (this->upgradeArmorRect.getGlobalBounds().contains(mousePos.x + _GAME_POSITION_X, mousePos.y + _GAME_POSITION_Y)) {
        return (3);
    }
    return (-1);
}

void SFMLHud::update() {
    m_waveText.setString("Wave: " + std::to_string(_waveNumber + 1) + "/" + std::to_string(_maxWaveNumber));
    m_moneyText.setString(std::to_string(_money) + " $");
}

void SFMLHud::drawBackground() {
    sf::Sprite background(m_backgroundTexture);
    _window->draw(background);
}

void SFMLHud::draw() {
    // Dessiner la texture du fond en répétition verticale
    
    // Afficher un sprite de coeur pour chaque vie restante
    this->towerRectangles.clear();
    int windowHeight = _window->getSize().y;
    int textureHeight = m_backgroundTexture.getSize().y * 2;
    _window->draw(this->levelTitleContainer);
    _window->draw(this->gameInfoContainer);
    _window->draw(m_levelText);
    int heartSize = 38;
    int heartSpacing = 12;
    
    for (int i = 0; i < _lifeNumber; i++) {
        sf::Sprite heartSprite(heartTexture);
        heartSprite.setPosition(80 + (heartSize + heartSpacing) * i, 400 + this->gameInfoOffset);
        heartSprite.setScale(1.4, 1.4);
        _window->draw(heartSprite);
    }
    
    _window->draw(coinSprite);
    m_moneyText.setPosition(170, 290+ this->gameInfoOffset);
    _window->draw(m_moneyText);
    m_waveText.setPosition(190, 145+ this->gameInfoOffset);
    _window->draw(m_waveText);
    textMessage.setPosition(70, 500 + this->gameInfoOffset);
    
    textMessage.setColor(sf::Color::White);
    textMessage.setCharacterSize(16);
    
    _window->draw(textMessage);
    if(selectedTower == nullptr){
        int towerInfoX = 1535;
        int towerInfoY = 50;

        if (towerStoreList.empty()) {
            std::cout << "towerStoreList is empty" << std::endl;
        }
        for (std::size_t i = 0; i < towerStoreList.size(); ++i) {

            sf::RectangleShape towerInfoRect(sf::Vector2f(500, 100));
            towerInfoRect.setPosition(towerInfoX - 150, towerInfoY - 20);
            sf::Color fillColor(0,0,0, 140);
            sf::Color outlineColor(255,255,255, 210);
            towerInfoRect.setFillColor(fillColor);
            towerInfoRect.setOutlineThickness(1);
            towerInfoRect.setOutlineColor(outlineColor);
            this->towerRectangles.push_back(towerInfoRect);
            _window->draw(towerInfoRect);
        sf::Text towerNameText;
        towerNameText.setFont(mainFont);
        towerNameText.setCharacterSize(24);
        towerNameText.setPosition(towerInfoX - 40, towerInfoY);
        if (towerStoreList[i].at(0)->getTowerName() == "SlowTower")
            towerNameText.setString("FreezeTower");
        else
            towerNameText.setString(towerStoreList[i].at(0)->getTowerName());
        _window->draw(towerNameText);

        // Afficher le coût de la tour
        sf::Text towerCostText;
        towerCostText.setFont(mainFont);
        towerCostText.setCharacterSize(18);
        towerCostText.setPosition(towerInfoX, towerInfoY + 35);
        towerCostText.setString("Cost: " + std::to_string(towerStoreList[i].at(0)->getCost()) + " coins");
        _window->draw(towerCostText);

        // Afficher le sprite de la tour
        sf::Sprite towerSprite = towerStoreList[i].at(0)->getTowerSprite();
        towerSprite.setPosition(towerInfoX - 95, towerInfoY + 30);
        _window->draw(towerSprite);
        towerInfoY += 120; // Avancer la position Y pour la prochaine tour
        }
        _window->draw(wallSprite);
        _window->draw(wallRect);
        _window->draw(wallPriceText);
    }else{
        sf::Text towerNameText;
        towerNameText.setFont(mainFont);
        towerNameText.setCharacterSize(24);
        sf::Vector2f newOrigin(towerNameText.getLocalBounds().width / 2.f, towerNameText.getLocalBounds().height / 2.f);
        towerNameText.setOrigin(newOrigin);
        towerNameText.setPosition(1550, 15 + this->towerSelectorOffset);
        towerNameText.setString(selectedTower->getTowerName());
        _window->draw(towerNameText);

        //tower selected info Menu - upgrade, sell buttons
        sf::Sprite towerSprite = selectedTower->getTowerSprite();
        towerSprite.setPosition(1650, 150 + this->towerSelectorOffset);
        towerSprite.setScale(1.3, 1.3);
        
        sf::Text towerLevelText;
        
        if(selectedTower->isMaxed()){
            towerLevelText.setString("Level: " + std::to_string(selectedTower->getLevel() + 1) + " (Max)");
        }else{
            towerLevelText.setString("Level: " + std::to_string(selectedTower->getLevel() + 1) + " -> " + std::to_string(selectedTower->getLevel() + 2) );
        }
        
        towerLevelText.setFont(mainFont);
        
        towerLevelText.setCharacterSize(24);
        towerLevelText.setPosition(1465, 250 + this->towerSelectorOffset);
        
        _window->draw(towerLevelText);

        sf::Text towerDamage;
        towerDamage.setFont(mainFont);
        towerDamage.setCharacterSize(24);
        towerDamage.setPosition(1465, 300 + this->towerSelectorOffset);
        std::string valueType("Damage: ");
        if (selectedTower->getTowerName() == "SpeedAuraTower")
            valueType = "Bonus: ";
        if(selectedTower->getTowerName() == "SlowTower")
            valueType = "Slow: ";
        if(!selectedTower->isMaxed()){
            towerDamage.setString(valueType + std::to_string(selectedTower->getDamage()) + " -> " + std::to_string(selectedTower->getUpgradeDamage()));
        }else{
            towerDamage.setString(valueType + std::to_string(selectedTower->getDamage()));
        }
        _window->draw(towerDamage);
        sf::Text towerRange;
        towerRange.setFont(mainFont);
        towerRange.setCharacterSize(24);
        towerRange.setPosition(1465, 350 + this->towerSelectorOffset);
        towerRange.setString("Range: " + std::to_string(selectedTower->getRange()));
        _window->draw(towerRange);
        sf::Text towerSpeed;
        towerSpeed.setFont(mainFont);
        towerSpeed.setCharacterSize(24);
        towerSpeed.setPosition(1465, 400 + this->towerSelectorOffset);
        std::stringstream stream;
        stream << std::fixed << std::setprecision(1) << 1000/(selectedTower->getTimeBetweenAttack()*1000);
        std::string str = stream.str();
        if (selectedTower->isSpeedBoosted()) {
            int bonusPercentValue = (1.0f - selectedTower->getSpeedBuff()) * 100.0f;
            std::string bonusPercentString = std::to_string(bonusPercentValue);
            towerSpeed.setString("Attack Speed: " + str + " +" + bonusPercentString + "%");
        }
        else
            towerSpeed.setString("Attack Speed: " + str);
        std::string stringArmorP("Armor penetration : " + std::to_string(selectedTower->getArmor()));
        sf::Text towerArmorP;
        towerArmorP.setFont(mainFont);
        towerArmorP.setCharacterSize(24);
        towerArmorP.setPosition(1465, 450 + this->towerSelectorOffset);
        towerArmorP.setString(stringArmorP);
        if (selectedTower->getTowerName() != "SpeedAuraTower") {
            _window->draw(towerSpeed);
            _window->draw(towerArmorP);
        }
        // DISPLAY UPGRADE BUTTON
        if(!selectedTower->isMaxed()){
            upgradeRect.setSize(sf::Vector2f(400, 80));
            upgradeRect.setPosition(1440, 595);
            upgradeRect.setFillColor(sf::Color::Transparent);
            upgradeRect.setOutlineThickness(1);
            upgradeRect.setOutlineColor(sf::Color::Yellow);
            sf::Text towerUpgradeCost;
            towerUpgradeCost.setString("UPGRADE \n" + std::to_string(selectedTower->getUpgradeCost()) + " coins");
            towerUpgradeCost.setFont(mainFont);
            towerUpgradeCost.setColor(sf::Color::Yellow);
            towerUpgradeCost.setCharacterSize(24);
            towerUpgradeCost.setPosition(1560, 605);
            _window->draw(upgradeRect);
            _window->draw(towerUpgradeCost);
            
        }
        // DISPLAY ARMOR PIERCE BUY BUTTON
        if(selectedTower->getTowerName() != "SpeedAuraTower" && selectedTower->getTowerName() != "SlowTower" ){
            this->upgradeArmorRect.setSize(sf::Vector2f(400, 80));
            this->upgradeArmorRect.setPosition(1440, 795);
            this->upgradeArmorRect.setFillColor(sf::Color::Transparent);
            this->upgradeArmorRect.setOutlineThickness(1);
            this->upgradeArmorRect.setOutlineColor(sf::Color::Magenta);
            sf::Text armorText;
            armorText.setString("+ 5 Armor p. \n   50 coins");
            armorText.setFont(mainFont);
            armorText.setColor(sf::Color::Magenta);
            armorText.setCharacterSize(24);
            armorText.setPosition(1545, 805);
            _window->draw(upgradeArmorRect);
            _window->draw(armorText);
        }
        // DISPLAY SELL BUTTON
        sellRect.setSize(sf::Vector2f(400, 80));
        sellRect.setPosition(1440, 695);
        sellRect.setFillColor(sf::Color::Transparent);
        sellRect.setOutlineThickness(1);
        sellRect.setOutlineColor(sf::Color::Red);
        sf::Text towerSellCost;
        towerSellCost.setString("    SELL \n" + std::to_string(selectedTower->getCost()/2) + " coins");
        towerSellCost.setFont(mainFont);
        towerSellCost.setColor(sf::Color::Red);
        towerSellCost.setCharacterSize(24);
        towerSellCost.setPosition(1560, 705);
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
