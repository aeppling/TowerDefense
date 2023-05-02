#ifndef UNTITLED1_SFMLHUD_HPP_
#define UNTITLED1_SFMLHUD_HPP_

#include <vector>
#include "../TDTowers/Tower.hpp"
#include "SFML/Graphics.hpp"
#include "../TDGraphics/SFMLLoader.hpp"


class Tower;
class SFMLHud{
private:
    int _lifeNumber;
    int _maxWaveNumber;
    int _waveNumber;
    int _level;
    sf::RenderWindow *_window;
    int _money;
    sf::Font mainFont;
    sf::Text m_waveText;
    sf::Text m_lifeText;
    sf::Text m_levelText;
    sf::Texture heartTexture;
    sf::Texture coinTexture;
    sf::Texture removeTexture;
    sf::Texture wallTexture;
    sf::Text m_moneyText;
    sf::Text wallPriceText;
    sf::Texture m_backgroundTexture;
    std::vector<Tower*> towerStoreList;
    sf::Sprite coinSprite;
    //sf::Sprite wallPriceImage;
    sf::Sprite removeSprite;
    sf::Sprite wallSprite;
    sf::RectangleShape removeRect;
    sf::RectangleShape wallRect;
public:
    SFMLHud(SFMLLoader *sfmlLoader, sf::RenderWindow *window, int gamePosX, int gamePoxY, int lifeNumber, int waveNumber, int money, int maxWaveNumber, int level);
    ~SFMLHud();
    void update();
    void draw();
    void setWave(int wave){ _waveNumber = wave;}
    void setLives(int life){ _lifeNumber = life;}
    void setMoney(int money){ _money = money;}
    void setMaxWave(int maxWave){ _maxWaveNumber = maxWave;}
    void setTowerStoreList(std::vector<Tower*> towerStoreList){ this->towerStoreList = towerStoreList;}
};
#endif // UNTITLED1_SFMLHUD_HPP_