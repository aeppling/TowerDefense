#ifndef UNTITLED1_SFMLHUD_HPP_
#define UNTITLED1_SFMLHUD_HPP_

#include <vector>
#include "../TDTowers/Tower.hpp"
#include "SFML/Graphics.hpp"
#include "../TDGraphics/SFMLLoader.hpp"


class Tower;
class SFMLHud{
private:
    Tower *selectedTower;
    bool isPaused;
    int _lifeNumber;
    int _maxWaveNumber;
    int _waveNumber;
    int _level;
    sf::RenderWindow *_window;
    int _money;
    sf::Text textMessage;
    sf::Font mainFont;
    sf::Text m_waveText;
    sf::Text m_lifeText;
    sf::Text m_levelText;
    sf::Texture heartTexture;
    sf::Texture coinTexture;
    sf::Texture removeTexture;
    sf::Texture wallTexture;
    sf::Texture pauseButtonTexture;
    sf::Texture volumeButtonTexture;
    sf::Texture homeButtonTexture;
    sf::Text m_moneyText;
    sf::Text wallPriceText;
    sf::Texture m_backgroundTexture;
    std::vector<std::vector<Tower*>> towerStoreList;
    sf::Sprite coinSprite;
    //sf::Sprite wallPriceImage;
    sf::Sprite removeSprite;
    sf::Sprite wallSprite;
    sf::Sprite pauseButtonSprite;
    sf::Sprite volumeButtonSprite;
    sf::Sprite homeButtonSprite;
    sf::RectangleShape removeRect;
    sf::RectangleShape wallRect;
    sf::RectangleShape upgradeRect;
    sf::RectangleShape upgradeArmorRect;
    sf::RectangleShape sellRect;

    std::vector<sf::RectangleShape> towerRectangles;
public:
    SFMLHud(SFMLLoader *sfmlLoader, sf::RenderWindow *window, int gamePosX, int gamePoxY, int lifeNumber, int waveNumber, int money, int maxWaveNumber, int level);
    ~SFMLHud();
    
    void update();
    void draw();
    void drawBackground();
    void setSelectedTower(Tower *tower){ selectedTower = tower;}
    void setWave(int wave){ _waveNumber = wave;}
    void setLives(int life){ _lifeNumber = life;}
    void setMoney(int money){ _money = money;}
    void setMaxWave(int maxWave){ _maxWaveNumber = maxWave;}
    void setTowerStoreList(std::vector<std::vector<Tower*>> towerStoreList){ this->towerStoreList = towerStoreList;}
    void setPaused(bool paused){ isPaused = paused;}
    bool getPaused(){  return isPaused;}
    void setMessage(std::string message){ textMessage.setString(message);}
    int checkForClick(sf::RenderWindow &window);
    int checkForSellUpgradeClick(sf::RenderWindow &window);
};
#endif // UNTITLED1_SFMLHUD_HPP_