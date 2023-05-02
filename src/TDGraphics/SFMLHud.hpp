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
    sf::RenderWindow *_window;
    int _money;
    sf::Font mainFont;
    sf::Text m_waveText;
    sf::Text m_lifeText;
    
    sf::Text m_moneyText;
    sf::Texture m_backgroundTexture;
    std::vector<Tower *> *towerStoreList;
public:
    SFMLHud(SFMLLoader *sfmlLoader, sf::RenderWindow *window, int gamePosX, int gamePoxY, int lifeNumber, int waveNumber, int money, int maxWaveNumber, std::vector<Tower *> *towerStoreList);
    ~SFMLHud();
    void update();
    void draw();
    void setWave(int wave){ _waveNumber = wave;}
    void setLives(int life){ _lifeNumber = life;}
    void setMoney(int money){ _money = money;}
};
#endif // UNTITLED1_SFMLHUD_HPP_