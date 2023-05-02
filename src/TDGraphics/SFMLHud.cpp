#include "SFMLHud.hpp"
#include <iostream>

SFMLHud::SFMLHud(SFMLLoader *sfmlLoader, sf::RenderWindow *window, int gamePosX, int gamePosY, int lifeNumber, int waveNumber, int money, int maxWaveNumber, int level) {
    
    _lifeNumber = lifeNumber;
    _waveNumber = waveNumber;
    _maxWaveNumber = maxWaveNumber;
    _money = money;
    _level = level;
    towerStoreList = std::vector<Tower*>();
    this->_window = window;
    this->mainFont.loadFromFile("Fonts/neuropol.otf");
    this->m_lifeText.setFont(this->mainFont);
    this->m_lifeText.setCharacterSize(32);
    this->m_waveText.setFont(this->mainFont);
    this->m_waveText.setCharacterSize(28);
    this->m_moneyText.setFont(this->mainFont);
    this->m_moneyText.setCharacterSize(28);
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
    coinSprite.setTexture(coinTexture);
    coinSprite.setPosition(50, 150);
    m_levelText.setFont(mainFont);
    m_levelText.setCharacterSize(28);
    m_levelText.setString("Level " + std::to_string(_level));
    m_levelText.setPosition(150, 5);
    removeSprite.setTexture(removeTexture);
    removeSprite.setPosition(100, 925);
    removeRect.setSize(sf::Vector2f(50, 50));
    removeRect.setPosition(100, 925);
    removeRect.setFillColor(sf::Color::Transparent);
    removeRect.setOutlineThickness(2);
    removeRect.setOutlineColor(sf::Color::White);
    wallSprite.setTexture(wallTexture);
    wallSprite.setPosition(200, 925);
    wallRect.setSize(sf::Vector2f(50, 50));
    wallRect.setPosition(200, 925);
    wallRect.setFillColor(sf::Color::Transparent);
    wallRect.setOutlineThickness(2);
    wallRect.setOutlineColor(sf::Color::White);
    wallPriceText.setFont(mainFont);
    wallPriceText.setCharacterSize(24);
    wallPriceText.setString("5 coins");
    wallPriceText.setPosition(257, 937);
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

    
    int towerInfoX = 75;
    int towerInfoY = 300;

    if (towerStoreList.empty()) {
        std::cout << "towerStoreList is empty" << std::endl;
    }
    for (std::size_t i = 0; i < towerStoreList.size(); ++i) {
    
    sf::Text towerNameText;
    towerNameText.setFont(mainFont);
    towerNameText.setCharacterSize(24);
    towerNameText.setPosition(towerInfoX, towerInfoY);
    towerNameText.setString(towerStoreList[i]->getTowerName());
    _window->draw(towerNameText);

    // Afficher le coût de la tour
    sf::Text towerCostText;
    towerCostText.setFont(mainFont);
    towerCostText.setCharacterSize(18);
    towerCostText.setPosition(towerInfoX, towerInfoY + 30);
    towerCostText.setString("Cost: " + std::to_string(towerStoreList[i]->getCost()) + " coins");
    _window->draw(towerCostText);

    // Afficher le sprite de la tour
    sf::Sprite towerSprite = towerStoreList[i]->getTowerSprite();
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
    _window->draw(removeSprite);
    _window->draw(removeRect);
    _window->draw(wallSprite);
    _window->draw(wallRect);
    _window->draw(wallPriceText);
    //_window->draw(wallPriceImage);
}