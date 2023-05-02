#include "SFMLHud.hpp"
#include <iostream>

SFMLHud::SFMLHud(SFMLLoader *sfmlLoader, sf::RenderWindow *window, int gamePosX, int gamePosY, int lifeNumber, int waveNumber, int money, int maxWaveNumber, std::vector<Tower *> *towerStoreList) {
    if (!m_backgroundTexture.loadFromFile("Sprites/hud_background.png")) {
        std::cout << "Error on loading texture..." << std::endl;
    }
    _lifeNumber = lifeNumber;
    _waveNumber = waveNumber;
    _maxWaveNumber = maxWaveNumber;
    _money = money;
    
    this->_window = window;
    this->mainFont.loadFromFile("Fonts/neuropol.otf");
    this->m_lifeText.setFont(this->mainFont);
    this->m_lifeText.setCharacterSize(32);
    this->m_waveText.setFont(this->mainFont);
    this->m_waveText.setCharacterSize(28);
    this->m_moneyText.setFont(this->mainFont);
    this->m_moneyText.setCharacterSize(28);

}

void SFMLHud::update() {
    m_waveText.setString("Wave: " + std::to_string(_waveNumber) + "/" + std::to_string(_maxWaveNumber));
    m_lifeText.setString("Lives: " + std::to_string(_lifeNumber));
    m_moneyText.setString(std::to_string(_money));
}

void SFMLHud::draw() {
    // Dessiner la texture du fond en répétition verticale
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
    // Afficher un sprite de coeur pour chaque vie restante
    sf::Texture heartTexture;
    if (!heartTexture.loadFromFile("Sprites/heart.png")) {
        std::cout << "Error on loading texture..." << std::endl;
    }
    int heartSize = 32;
    int heartSpacing = 10;
    for (int i = 0; i < _lifeNumber; i++) {
        sf::Sprite heartSprite(heartTexture);
        heartSprite.setPosition(50 + (heartSize + heartSpacing) * i, 100);
        _window->draw(heartSprite);
    }

    sf::Texture coinTexture;
    if (!coinTexture.loadFromFile("Sprites/coin.png")) {
        std::cout << "Error on loading texture..." << std::endl;
    }
    sf::Sprite coinSprite(coinTexture);
     m_moneyText.setPosition(150, 225);
     coinSprite.setPosition(50, 200);
    _window->draw(coinSprite);
    _window->draw(m_moneyText);

    m_waveText.setPosition(50, 150);
    _window->draw(m_waveText);

    /*
    int towerInfoX = 50;
    int towerInfoY = 300;
    if (towerStoreList == nullptr) {
         std::cout << "towerStoreList is null" << std::endl;
    }
    
    std::vector<Tower*>& towerStoreListRef = *towerStoreList;
    if (towerStoreListRef.empty()) {
        std::cout << "towerStoreList is empty" << std::endl;
    } else {
        std::cout << "towerStoreList.size() = " << towerStoreListRef.size() << std::endl;


        for (std::size_t i = 0; i < towerStoreListRef.size(); ++i) {
        std::cout << "boucle" << std::endl;
        sf::Text towerNameText;
        towerNameText.setFont(mainFont);
        towerNameText.setCharacterSize(20);
        towerNameText.setPosition(towerInfoX, towerInfoY);
       towerNameText.setString(towerStoreListRef[i]->getTowerName());
        _window->draw(towerNameText);

        // Afficher le coût de la tour
        sf::Text towerCostText;
        towerCostText.setFont(mainFont);
        towerCostText.setCharacterSize(16);
        towerCostText.setPosition(towerInfoX, towerInfoY + 30);
        towerCostText.setString("Cost: " + std::to_string(towerStoreListRef[i]->getCost()) + " coins");
        _window->draw(towerCostText);

        towerInfoX += 200; // Avancer la position X pour la prochaine tour
        }
    }*/
}
