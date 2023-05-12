//
// Created by adrie on 10/05/2023.
//

#include <iostream>

#include "Menus.hpp"

Menus::Menus(int winSizeX, int winSizeY, TDPlayerSave &playerData) : _winSizeX(winSizeX), _winSizeY(winSizeY), _playerData(playerData) {
    this->_players = "single";
    this->_isIpEntering = false;
    this->_ipAddressField = "";
    this->_isInSettings = false;
    // PLANETS
    if (!this->_planet1txt.loadFromFile("Sprites/Planets/planet03.png"))
        std::cout << "Planet sprite not loaded correctly" << std::endl;
    if (!this->_planet2txt.loadFromFile("Sprites/Planets/planet07.png"))
        std::cout << "Planet sprite not loaded correctly" << std::endl;
    if (!this->_planet3txt.loadFromFile("Sprites/Planets/planet09.png"))
        std::cout << "Planet sprite not loaded correctly" << std::endl;
    // ICONS
    if (!this->_singleIcon.loadFromFile("Icons/singleIcon.png"))
        std::cout << "Menu icon not loaded correctly" << std::endl;
    if (!this->_multiIcon.loadFromFile("Icons/multiIcon.png"))
        std::cout << "Menu icon not loaded correctly" << std::endl;
    if (!this->_tutoIcon.loadFromFile("Icons/tutoIcon.png"))
        std::cout << "Menu icon not loaded correctly" << std::endl;
    if (!this->_settingsIcon.loadFromFile("Icons/settingsIcon.png"))
        std::cout << "Menu icon not loaded correctly" << std::endl;
    if (!this->_hostIcon.loadFromFile("Icons/hostIcon.png"))
        std::cout << "Menu icon not loaded correctly" << std::endl;
    if (!this->_joinIcon.loadFromFile("Icons/joinIcon.png"))
        std::cout << "Menu icon not loaded correctly" << std::endl;
    // BACKGROUNDS
    if (!this->_backgroundStars.loadFromFile("Sprites/stars_texture.png"))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_backgroundHome.loadFromFile("Sprites/Backgrounds/titleScreen.png")))
        std::cout << "Error on loading menus textures..." << std::endl;
    if (!(this->_backgroundSingleplayer.loadFromFile("Sprites/Backgrounds/backgroundLevels.png")))
        std::cout << "Error on loading menus textures..." << std::endl;
    if (!(this->_backgroundLevels.loadFromFile("Sprites/Backgrounds/backgroundLevels.png")))
        std::cout << "Error on loading menus textures..." << std::endl;
    if (!(this->_backgroundSettings.loadFromFile("Sprites/Backgrounds/backgroundSettings.png")))
        std::cout << "Error on loading menus textures..." << std::endl;
    if (!(this->_backgroundTutorial.loadFromFile("Sprites/Backgrounds/howToPlayScreen.png")))
        std::cout << "Error on loading menus textures..." << std::endl;
    // FONTS
    if (!(this->_mainFont.loadFromFile("Fonts/neuropol.otf")))
        std::cout << "Error on loading menus textures..." << std::endl;
    if (!this->_fontTitle.loadFromFile("Fonts/ModernWarfare-OV7KP.ttf"))
        std::cout << "Title font not loaded correctly" << std::endl;
}

void Menus::createText(std::string text, sf::Font &font, int characterSize, int posX, int posY) {
    sf::Text *textPtr = new sf::Text;
    textPtr->setString(text);
    textPtr->setFont(font);
    textPtr->setCharacterSize(characterSize);
    sf::Vector2f newOriginText2(textPtr->getLocalBounds().width / 2.f, textPtr->getLocalBounds().height / 2.f);
    textPtr->setOrigin(newOriginText2);
    textPtr->setPosition(posX, posY);
    this->_visibleText.push_back(textPtr);
}

void Menus::createSlider(float value, float posX, float posY, std::string type) {
   // actualVolume = this->_globalVolume / 100.f * this->_globalVolumeSliderBackground.getSize().x;
    sf::RectangleShape background(sf::Vector2f(600.f, 40.f));
    background.setFillColor(sf::Color::White);
    sf::Vector2f newOrigin(background.getLocalBounds().width / 2.f, background.getLocalBounds().height / 2.f);
    background.setOrigin(newOrigin);
    background.setPosition(posX, posY);
    if (type == "global")
        value = this->_playerData.getGlobalVolume() / 100.f * background.getSize().x;
    else if (type == "music")
        value = this->_playerData.getMusicVolume() / 100.f * background.getSize().x;
    else if (type == "sound")
        value = this->_playerData.getSoundVolume() / 100.f * background.getSize().x;
    sf::RectangleShape slider(sf::Vector2f(value, 40.f));
    slider.setFillColor(sf::Color::Cyan);
    slider.setOrigin(newOrigin);
    slider.setPosition(posX, posY);
    if (type == "global") {
        this->_globalVolumeSliderBackground = background;
        this->_globalVolumeSlider = slider;
    }
    else if (type == "music") {
        this->_musicVolumeSliderBackground = background;
        this->_musicVolumeSlider = slider;
    }
    else if (type == "sound") {
        this->_soundVolumeSliderBackground = background;
        this->_soundVolumeSlider = slider;
    }
}

void Menus::loadHome() {
    this->_players = "single";
    this->_isIpEntering = false;
    this->_ipAddressField = "";
    this->_isInSettings = false;

    this->deleteVisibleButtons();
    this->deleteVisibleSprites();
    this->deleteVisibleText();
    this->deleteVisibleRectangle();

    // SETUP BUTTON
    MenusButton *singleplayerButton = new MenusButton(500, 70, true, "Singleplayer", "singleplayer", this->_mainFont);
    MenusButton *multiplayerButton = new MenusButton(500, 70, true, "Multiplayer", "multiplayer", this->_mainFont);
    MenusButton *howToButton = new MenusButton(500, 70, true, "How To Play", "tutorial", this->_mainFont);
    MenusButton *settingsButton = new MenusButton(500, 70, true, "Settings", "settings", this->_mainFont);
    MenusButton *exitButton = new MenusButton(300, 70, true, "Exit Game", "exit", this->_mainFont);

    singleplayerButton->setPosition(_winSizeX / 2, 400);
    multiplayerButton->setPosition(_winSizeX / 2, 500);
    howToButton->setPosition(_winSizeX / 2, 600);
    settingsButton->setPosition(_winSizeX / 2, 700);
    exitButton->setPosition(_winSizeX / 2, 850);

    this->_visibleButtons.push_back(singleplayerButton);
    this->_visibleButtons.push_back(multiplayerButton);
    this->_visibleButtons.push_back(howToButton);
    this->_visibleButtons.push_back(settingsButton);
    this->_visibleButtons.push_back(exitButton);

    // SETUP ICON SPRITES
    sf::Sprite *singleIcon = new sf::Sprite;
    singleIcon->setTexture(this->_singleIcon);
    sf::Vector2f newOriginIcon1(singleIcon->getLocalBounds().width / 2.f, singleIcon->getLocalBounds().height / 2.f);
    singleIcon->setOrigin(newOriginIcon1);
    singleIcon->setPosition((_winSizeX / 2) - 200, 395);
    singleIcon->setScale(0.23, 0.23);
    this->_visibleSprites.push_back(singleIcon);

    sf::Sprite *multiIcon = new sf::Sprite;
    multiIcon->setTexture(this->_multiIcon);
    sf::Vector2f newOriginIcon2(multiIcon->getLocalBounds().width / 2.f, multiIcon->getLocalBounds().height / 2.f);
    multiIcon->setOrigin(newOriginIcon2);
    multiIcon->setPosition((_winSizeX / 2) - 200, 495);
    multiIcon->setScale(0.23, 0.23);
    this->_visibleSprites.push_back(multiIcon);

    sf::Sprite *tutoIcon = new sf::Sprite;
    tutoIcon->setTexture(this->_tutoIcon);
    sf::Vector2f newOriginIcon3(tutoIcon->getLocalBounds().width / 2.f, tutoIcon->getLocalBounds().height / 2.f);
    tutoIcon->setOrigin(newOriginIcon3);
    tutoIcon->setPosition((_winSizeX / 2) - 200, 595);
    tutoIcon->setScale(0.23, 0.23);
    this->_visibleSprites.push_back(tutoIcon);

    sf::Sprite *settingsIcon = new sf::Sprite;
    settingsIcon->setTexture(this->_settingsIcon);
    sf::Vector2f newOriginIcon4(settingsIcon->getLocalBounds().width / 2.f, settingsIcon->getLocalBounds().height / 2.f);
    settingsIcon->setOrigin(newOriginIcon4);
    settingsIcon->setPosition((_winSizeX / 2) - 200, 695);
    settingsIcon->setScale(0.23, 0.23);
    this->_visibleSprites.push_back(settingsIcon);

    // SETUP BACKGROUND
    this->_actualBackground.setTexture(this->_backgroundHome);
    this->_actualBackground.setPosition(0, 0);
    this->_actualBackground.setScale(1, 1);
}

void Menus::loadSingleplayer() {
    this->deleteVisibleButtons();
    this->deleteVisibleSprites();
    this->deleteVisibleText();
    this->deleteVisibleRectangle();

    // BUTTONS SETUP
    MenusButton *world1 = new MenusButton(400, 600, true, "Terra", "planet1", this->_mainFont);
    MenusButton *world2 = new MenusButton(400, 600, true, "Frost", "planet2", this->_mainFont);
    MenusButton *world3 = new MenusButton(400, 600, true, "Quasaros", "planet3", this->_mainFont);
    MenusButton *backhome = new MenusButton(400, 80, true, "Back To Home", "home", this->_mainFont);
    world1->getText()->setCharacterSize(40);
    world2->getText()->setCharacterSize(40);
    world3->getText()->setCharacterSize(40);

    int offset = (_winSizeX / 5) + 70;
    world1->setPosition(offset, 500);
    world2->setPosition(offset + 500, 500);
    world3->setPosition(offset + 1000, 500);
    world1->getText()->setPosition(world1->getText()->getPosition().x - 40, world1->getText()->getPosition().y + 170);
    world2->getText()->setPosition(world2->getText()->getPosition().x - 30, world2->getText()->getPosition().y + 170);
    world3->getText()->setPosition(world3->getText()->getPosition().x - 50, world3->getText()->getPosition().y + 170);
    backhome->setPosition(_winSizeX / 2, 900);

    this->_visibleButtons.push_back(world1);
    this->_visibleButtons.push_back(world2);
    this->_visibleButtons.push_back(world3);
    this->_visibleButtons.push_back(backhome);

    // BACKGROUND SETUP
    this->_actualBackground.setTexture(this->_backgroundSingleplayer);
    this->_actualBackground.setPosition(0, 0);
    this->_actualBackground.setScale(1, 1);

    // OTHERS SPRITE SET UP

    sf::Sprite *planet1Spr = new sf::Sprite;
    sf::Sprite *planet2Spr = new sf::Sprite;
    sf::Sprite *planet3Spr = new sf::Sprite;

    planet1Spr->setTexture(this->_planet1txt);
    planet2Spr->setTexture(this->_planet2txt);
    planet3Spr->setTexture(this->_planet3txt);

    sf::Vector2f newOriginText1(planet1Spr->getLocalBounds().width / 2.f, planet1Spr->getLocalBounds().height / 2.f);
    planet1Spr->setOrigin(newOriginText1);
    sf::Vector2f newOriginText2(planet2Spr->getLocalBounds().width / 2.f, planet2Spr->getLocalBounds().height / 2.f);
    planet2Spr->setOrigin(newOriginText2);
    sf::Vector2f newOriginText3(planet3Spr->getLocalBounds().width / 2.f, planet3Spr->getLocalBounds().height / 2.f);
    planet3Spr->setOrigin(newOriginText3);

    planet1Spr->setPosition(offset, 400);
    planet2Spr->setPosition(offset + 500, 400);
    planet3Spr->setPosition(offset + 1000, 400);
    planet1Spr->setScale(0.25, 0.25);
    planet2Spr->setScale(0.25, 0.25);
    planet3Spr->setScale(0.25, 0.25);

    this->_visibleSprites.push_back(planet1Spr);
    this->_visibleSprites.push_back(planet2Spr);
    this->_visibleSprites.push_back(planet3Spr);
}

void Menus::loadMultiplayer() {
    this->_players = "multi";
    this->_isIpEntering = false;
    this->_ipAddressField = "";
    this->deleteVisibleButtons();
    this->deleteVisibleSprites();
    this->deleteVisibleText();
    this->deleteVisibleRectangle();

    // BUTTONS SETUP
    MenusButton *host = new MenusButton(400, 600, true, "Host", "singleplayer", this->_mainFont);
    MenusButton *join = new MenusButton(400, 600, true, "Join", "join", this->_mainFont);
    MenusButton *backhome = new MenusButton(400, 80, true, "Back To Home", "home", this->_mainFont);
    host->getText()->setCharacterSize(40);
    join->getText()->setCharacterSize(40);

    int offset = (_winSizeX / 2) - 240;
    host->setPosition(offset, 500);
    join->setPosition(offset + 500, 500);
    host->getText()->setPosition(host->getText()->getPosition().x - 30, host->getText()->getPosition().y + 170);
    join->getText()->setPosition(join->getText()->getPosition().x - 30, join->getText()->getPosition().y + 170);
    backhome->setPosition(_winSizeX / 2, 900);

    this->_visibleButtons.push_back(host);
    this->_visibleButtons.push_back(join);
    this->_visibleButtons.push_back(backhome);

    // ICON SETUP
    sf::Sprite *hostIcon = new sf::Sprite;
    hostIcon->setTexture(this->_hostIcon);
    sf::Vector2f newOriginIcon1(hostIcon->getLocalBounds().width / 2.f, hostIcon->getLocalBounds().height / 2.f);
    hostIcon->setOrigin(newOriginIcon1);
    hostIcon->setPosition(offset, 450);
    hostIcon->setScale(0.8, 0.8);
    this->_visibleSprites.push_back(hostIcon);

    sf::Sprite *joinIcon = new sf::Sprite;
    joinIcon->setTexture(this->_joinIcon);
    sf::Vector2f newOriginIcon2(joinIcon->getLocalBounds().width / 2.f, joinIcon->getLocalBounds().height / 2.f);
    joinIcon->setOrigin(newOriginIcon2);
    joinIcon->setPosition(offset + 500, 450);
    joinIcon->setScale(0.8, 0.8);
    this->_visibleSprites.push_back(joinIcon);

    // BACKGROUND SETUP
    this->_actualBackground.setTexture(this->_backgroundSingleplayer);
    this->_actualBackground.setPosition(0, 0);
    this->_actualBackground.setScale(1, 1);

}

void Menus::loadHostLobby() {
    this->deleteVisibleButtons();
    this->deleteVisibleSprites();
    this->deleteVisibleText();
    this->deleteVisibleRectangle();

    MenusButton *back = new MenusButton(400, 80, true, "Back to host choice", "multiplayer", this->_mainFont);
    back->setPosition(_winSizeX / 2, 900);
    this->_visibleButtons.push_back(back);


    this->_actualBackground.setTexture(this->_backgroundStars);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);
}

void Menus::loadHost(std::string hostIpAddress) {
    this->deleteVisibleButtons();
    this->deleteVisibleSprites();
    this->deleteVisibleText();
    this->deleteVisibleRectangle();

    MenusButton *back = new MenusButton(400, 80, true, "Back to planet choice", "singleplayer", this->_mainFont);
    back->setPosition(_winSizeX / 2, 900);
    this->_visibleButtons.push_back(back);

    this->createText("Waiting for player connection...\n\n Enter this ip : " + hostIpAddress, this->_mainFont, 60, this->_winSizeX / 2, this->_winSizeY / 2.5);
   /* std::string title("Waiting for player connection...\n\n Enter this ip : " + hostIpAddress );
    sf::Text *mainTitle = new sf::Text;
    mainTitle->setString(title);
    mainTitle->setFont(this->_mainFont);
    mainTitle->setCharacterSize(60);
    sf::Vector2f newOriginTitle(mainTitle->getLocalBounds().width / 2.f, mainTitle->getLocalBounds().height / 2.f);
    mainTitle->setOrigin(newOriginTitle);
    mainTitle->setPosition(this->_winSizeX / 2, this->_winSizeY / 2.5);
    this->_visibleText.push_back(mainTitle);*/

    this->_actualBackground.setTexture(this->_backgroundStars);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);
}

void Menus::loadJoin() {
    this->deleteVisibleButtons();
    this->deleteVisibleSprites();
    this->deleteVisibleText();
    this->deleteVisibleRectangle();
    this->_isIpEntering = true;

    MenusButton *back = new MenusButton(400, 80, true, "Back to host choice", "multiplayer", this->_mainFont);
    MenusButton *joinTest = new MenusButton(600, 80, true, "Join", "jointest", this->_mainFont);
    joinTest->setPosition(_winSizeX / 2, 700);
    back->setPosition(_winSizeX / 2, 900);
    this->_visibleButtons.push_back(joinTest);
    this->_visibleButtons.push_back(back);

    // INFO TEXT
    std::string title("Enter host IP address :");
    sf::Text *infoText = new sf::Text;
    infoText->setString(title);
    infoText->setFont(this->_mainFont);
    infoText->setCharacterSize(60);
    sf::Vector2f newOriginTitle(infoText->getLocalBounds().width / 2.f, infoText->getLocalBounds().height / 2.f);
    infoText->setOrigin(newOriginTitle);
    infoText->setPosition(this->_winSizeX / 2, this->_winSizeY / 6);
    this->_visibleText.push_back(infoText);

    // TEXT FIELD INPUT
    sf::RectangleShape textField(sf::Vector2f(200.f, 30.f));
    textField.setFillColor(sf::Color::White);
    textField.setOutlineThickness(2.f);
    textField.setOutlineColor(sf::Color::Black);
    textField.setPosition(300.f, 200.f);
    std::string ipAdressText(this->_ipAddressField);
    sf::Text *inputText = new sf::Text;
    inputText->setString(ipAdressText);
    inputText->setFont(this->_mainFont);
    inputText->setCharacterSize(60);
    sf::Vector2f newOriginInfo(inputText->getLocalBounds().width / 2.f, inputText->getLocalBounds().height / 2.f);
    inputText->setOrigin(newOriginInfo);
    inputText->setPosition(this->_winSizeX / 2, this->_winSizeY / 2.5);
    inputText->setFillColor(sf::Color::White);
    this->_visibleText.push_back(inputText);

    // BACKGROUND
    this->_actualBackground.setTexture(this->_backgroundSingleplayer);
    this->_actualBackground.setPosition(0, 0);
    this->_actualBackground.setScale(1, 1);
}

void Menus::loadJoinTest() {
    this->deleteVisibleButtons();
    this->deleteVisibleSprites();
    this->deleteVisibleText();
    this->deleteVisibleRectangle();

    MenusButton *backhome = new MenusButton(400, 80, true, "Back To Home", "home", this->_mainFont);
    backhome->setPosition(_winSizeX / 2, 900);
    this->_visibleButtons.push_back(backhome);

    // INFO TEXT
    std::string title("Trying to connect to host...");
    sf::Text *mainTitle = new sf::Text;
    mainTitle->setString(title);
    mainTitle->setFont(this->_mainFont);
    mainTitle->setCharacterSize(60);
    sf::Vector2f newOriginTitle(mainTitle->getLocalBounds().width / 2.f, mainTitle->getLocalBounds().height / 2.f);
    mainTitle->setOrigin(newOriginTitle);
    mainTitle->setPosition(this->_winSizeX / 2, this->_winSizeY / 2.5);

    this->_visibleText.push_back(mainTitle);
    this->_actualBackground.setTexture(this->_backgroundStars);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);
}

void Menus::loadSettings() {
    this->deleteVisibleButtons();
    this->deleteVisibleSprites();
    this->deleteVisibleText();
    this->deleteVisibleRectangle();
    this->_isInSettings = true;

    MenusButton *backhome = new MenusButton(400, 80, true, "Save & Back Home", "home", this->_mainFont);
    backhome->setPosition(_winSizeX / 2, 900);
    this->_visibleButtons.push_back(backhome);

    // VOLUMES SLIDERS
    this->createSlider(this->_playerData.getGlobalVolume(), (this->_winSizeX / 2) + 300, 400, "global");
    this->createSlider(this->_playerData.getGlobalVolume(), (this->_winSizeX / 2) + 300, 550, "music");
    this->createSlider(this->_playerData.getGlobalVolume(), (this->_winSizeX / 2) + 300, 700, "sound");

    // DIFFICULTY TEXT & Button
    this->createText("Difficulty :", this->_mainFont, 34, (this->_winSizeX / 2) - 240, 240);
    MenusButton *difficultySetter;
    if (this->_playerData.getDifficulty() == 2)
        difficultySetter = new MenusButton(350, 50, true, "Normal", "set-normal", this->_mainFont);
    else if (this->_playerData.getDifficulty() == 3)
        difficultySetter = new MenusButton(350, 50, true, "Hard", "set-hard", this->_mainFont);
    else
        difficultySetter = new MenusButton(350, 50, true, "Easy", "set-easy", this->_mainFont);
    difficultySetter->setPosition((this->_winSizeX / 2) + 300, 250);
    this->_visibleButtons.push_back(difficultySetter);

    // VOLUME TEXT
    this->createText("Global volume :", this->_mainFont, 34, (this->_winSizeX / 2) - 300, 390);
    this->createText("Music volume :", this->_mainFont, 34, (this->_winSizeX / 2) - 300, 540);
    this->createText("Sound volume :", this->_mainFont, 34, (this->_winSizeX / 2) - 300, 690);

    // BACKGROUND
    this->_actualBackground.setTexture(this->_backgroundSettings);
    this->_actualBackground.setPosition(0, 0);
    this->_actualBackground.setScale(1, 1);
}

void Menus::reloadVolume(int newVolume, std::string type) {

    float newValue = newVolume / 100.f * this->_globalVolumeSliderBackground.getSize().x;
    if (type == "global")
        this->_globalVolumeSlider.setSize(sf::Vector2f(newValue, this->_globalVolumeSlider.getSize().y));
    else if (type == "music")
        this->_musicVolumeSlider.setSize(sf::Vector2f(newValue, this->_musicVolumeSlider.getSize().y));
    else if (type == "sound")
        this->_soundVolumeSlider.setSize(sf::Vector2f(newValue, this->_soundVolumeSlider.getSize().y));
    else
        return ;
}

void Menus::setDifficultyEasy() {
    this->_playerData.setDifficulty(2);
    this->loadSettings();
}

void Menus::setDifficultyNormal() {
    this->_playerData.setDifficulty(3);
    this->loadSettings();
}

void Menus::setDifficultyHard() {
    this->_playerData.setDifficulty(1);
    this->loadSettings();
}

void Menus::loadTutorial() {
    this->deleteVisibleButtons();
    this->deleteVisibleSprites();
    this->deleteVisibleText();
    this->deleteVisibleRectangle();

    MenusButton *backhome = new MenusButton(200, 80, true, "< Back", "home", this->_mainFont);
    backhome->setPosition((this->_winSizeX / 2) - 800, this->_winSizeY - 150);
    this->_visibleButtons.push_back(backhome);

    MenusButton *unitManual = new MenusButton(400, 80, true, "Towers Manual", "towermanual", this->_mainFont);
    unitManual->setPosition((this->_winSizeX / 2) - 250, this->_winSizeY - 150);
    this->_visibleButtons.push_back(unitManual);

    MenusButton *towerManual = new MenusButton(400, 80, true, "Units Manual", "unitmanual", this->_mainFont);
    towerManual->setPosition((this->_winSizeX / 2) + 250, this->_winSizeY - 150);
    this->_visibleButtons.push_back(towerManual);

    this->_actualBackground.setTexture(this->_backgroundTutorial);
    this->_actualBackground.setPosition(0, 0);
    this->_actualBackground.setScale(1, 1);
}

void Menus::loadLevelsPlanet1() {
    this->deleteVisibleButtons();
    this->deleteVisibleSprites();
    this->deleteVisibleText();
    this->deleteVisibleRectangle();

    // BACK BUTTON & BACKGROUND
    MenusButton *back = new MenusButton(400, 80, true, "Back To Planets", "singleplayer", this->_mainFont);
    back->setPosition(_winSizeX / 2, 900);
    this->_visibleButtons.push_back(back);
    this->_actualBackground.setTexture(this->_backgroundSingleplayer);
    this->_actualBackground.setPosition(0, 0);
    this->_actualBackground.setScale(1, 1);
    // LEVELS SET
    int number_of_level = 10;
    int i = 0;
    int vertical_offset = 0;
    int horizontal_offset = 0;
    while (i < number_of_level) {
        if (i == 5) {
            vertical_offset = 300;
            horizontal_offset = 0;
        }
        std::string textDisplayStr("Level " + std::to_string(i + 1));
        std::string shortNameStr("planet1level" + std::to_string(i + 1));
        MenusButton *newLevel;
        if (this->_playerData.getUnlockedPlanet1() < i + 1)
            newLevel = new MenusButton(300, 300, false, textDisplayStr, "locked", this->_mainFont);
        else
            newLevel = new MenusButton(300, 300, true, textDisplayStr, shortNameStr, this->_mainFont);
        newLevel->setPosition(360 + (horizontal_offset * 300), 350 + vertical_offset);
        horizontal_offset++;
        this->_visibleButtons.push_back(newLevel);
        i++;
    }
}

void Menus::loadLevelsPlanet2() {
    this->deleteVisibleButtons();
    this->deleteVisibleSprites();
    this->deleteVisibleText();
    this->deleteVisibleRectangle();

    // BACK BUTTON & BACKGROUND
    MenusButton *back = new MenusButton(400, 80, true, "Back To Planets", "singleplayer", this->_mainFont);
    back->setPosition(_winSizeX / 2, 900);
    this->_visibleButtons.push_back(back);
    this->_actualBackground.setTexture(this->_backgroundSingleplayer);
    this->_actualBackground.setPosition(0, 0);
    this->_actualBackground.setScale(1, 1);
    // LEVELS SET
    int number_of_level = 10;
    int i = 0;
    int vertical_offset = 0;
    int horizontal_offset = 0;
    while (i < number_of_level) {
        if (i == 5) {
            vertical_offset = 300;
            horizontal_offset = 0;
        }
        std::string textDisplayStr("Level " + std::to_string(i + 1));
        std::string shortNameStr("planet2level" + std::to_string(i + 1));
        MenusButton *newLevel;
        if (this->_playerData.getUnlockedPlanet2() < i + 1)
            newLevel = new MenusButton(300, 300, false, textDisplayStr, "locked", this->_mainFont);
        else
            newLevel = new MenusButton(300, 300, true, textDisplayStr, shortNameStr, this->_mainFont);
        newLevel->setPosition(360 + (horizontal_offset * 300), 350 + vertical_offset);
        horizontal_offset++;
        this->_visibleButtons.push_back(newLevel);
        i++;
    }
}

void Menus::loadLevelsPlanet3() {
    this->deleteVisibleButtons();
    this->deleteVisibleSprites();
    this->deleteVisibleText();
    this->deleteVisibleRectangle();

    // BACK BUTTON & BACKGROUND
    MenusButton *back = new MenusButton(400, 80, true, "Back To Planets", "singleplayer", this->_mainFont);
    back->setPosition(_winSizeX / 2, 900);
    this->_visibleButtons.push_back(back);
    this->_actualBackground.setTexture(this->_backgroundSingleplayer);
    this->_actualBackground.setPosition(0, 0);
    this->_actualBackground.setScale(1, 1);
    // LEVELS SET
    int number_of_level = 10;
    int i = 0;
    int vertical_offset = 0;
    int horizontal_offset = 0;
    while (i < number_of_level) {
        if (i == 5) {
            vertical_offset = 300;
            horizontal_offset = 0;
        }
        std::string textDisplayStr("Level " + std::to_string(i + 1));
        std::string shortNameStr("planet3level" + std::to_string(i + 1));
        MenusButton *newLevel;
        if (this->_playerData.getUnlockedPlanet3() < i + 1)
            newLevel = new MenusButton(300, 300, false, textDisplayStr, "locked", this->_mainFont);
        else
            newLevel = new MenusButton(300, 300, true, textDisplayStr, shortNameStr, this->_mainFont);
        newLevel->setPosition(360 + (horizontal_offset * 300), 350 + vertical_offset);
        horizontal_offset++;
        this->_visibleButtons.push_back(newLevel);
        i++;
    }
}

void Menus::drawMenu(sf::RenderWindow &window) {
    sf::Sprite backgroundStarsSpr(this->_backgroundStars);
    window.draw(backgroundStarsSpr);
    window.draw(this->_actualBackground);
    int i = 0;
    while (i < this->_visibleButtons.size()) {
        window.draw(*this->_visibleButtons.at(i)->getText());
        window.draw(*this->_visibleButtons.at(i)->getRectangle());
        i++;
    }
    i = 0;
    while (i < this->_visibleSprites.size()) {
        window.draw(*this->_visibleSprites.at(i));
        i++;
    }
    i = 0;
    while (i < this->_visibleText.size()) {
        window.draw(*this->_visibleText.at(i));
        i++;
    }
    if (!this->_visibleRectangle.empty()) {
        i = 0;
        while (i < this->_visibleRectangle.size()) {
            window.draw(*this->_visibleRectangle.at(i));
            i++;
        }
    }
    if (this->_isInSettings) {
        window.draw(this->_globalVolumeSliderBackground);
        window.draw(this->_globalVolumeSlider);
        window.draw(this->_musicVolumeSliderBackground);
        window.draw(this->_musicVolumeSlider);
        window.draw(this->_soundVolumeSliderBackground);
        window.draw(this->_soundVolumeSlider);
    }
}

std::string Menus::loadMenuByName(std::string name) {
    if (name == "singleplayer") {
        this->loadSingleplayer();
        return ("no");
    }
    else if (name == "multiplayer") {
        this->loadMultiplayer();
        return ("no");
    }
    else if (name == "tutorial") {
        this->loadTutorial();
        return ("no");
    }
    else if (name == "settings") {
        this->loadSettings();
        return ("settings");
    }
    else if (name == "set-easy") {
        this->setDifficultyEasy();
        return ("settings");
    }
    else if (name == "set-normal") {
        this->setDifficultyNormal();
        return ("settings");
    }
    else if (name == "set-hard") {
        this->setDifficultyHard();
        return ("settings");
    }
    else if (name == "home") {
        this->loadHome();
        return ("no");
    }
    else if (name == "host") {
        this->loadHost("");
        return ("hostwait");
    }
    else if (name == "join") {
        this->loadJoin();
        return ("no");
    }
    else if (name == "jointest") {
        this->loadJoinTest();
        return ("ip:" + this->_ipAddressField);
    }
    else if (name == "planet1") {
        this->loadLevelsPlanet1();
        return ("no");
    }
    else if (name == "planet2") {
        this->loadLevelsPlanet2();
        return ("no");
    }
    else if (name == "planet3") {
        this->loadLevelsPlanet3();
        return ("no");
    }
    else
        return (name + this->_players); // COMPACT WITH DIFFICULTY ????
    // ELSE RETURN BECAUSE IT IS A LEVEL & PLANET INFORMATION
}

std::string Menus::checkForClick(sf::Vector2i mousePos) {
    int i = 0;

    std::string whichClick;
    while (i < this->_visibleButtons.size()) {
        whichClick = this->_visibleButtons.at(i)->isClicked(mousePos.x, mousePos.y);
        if (whichClick == "exit")
            return (whichClick);
        else if (whichClick != "no") {
            std::string answer = this->loadMenuByName(whichClick);
            if (answer != "no")
                return (answer);
            else
                break;
        }
        i++;
    }
    return ("no");
}

bool Menus::checkIfVolumeClicked(sf::Vector2i mousePosition, TDPlayerSave &playerSave, std::string saveFile) {
    sf::FloatRect globalSliderBorder = this->_globalVolumeSliderBackground.getGlobalBounds();
    sf::FloatRect musicSliderBorder = this->_musicVolumeSliderBackground.getGlobalBounds();
    sf::FloatRect soundSliderBorder = this->_soundVolumeSliderBackground.getGlobalBounds();

    float newVolume = -1;
    if (globalSliderBorder.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        newVolume = (mousePosition.x - globalSliderBorder.left) / globalSliderBorder.width * 100.f;
        newVolume = std::max(0.f, std::min(100.f, newVolume));
        playerSave.setGlobalVolume(newVolume);
        this->_playerData.setGlobalVolume(newVolume);
        reloadVolume(newVolume, "global");
    }
    else if (musicSliderBorder.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        newVolume = (mousePosition.x - musicSliderBorder.left) / musicSliderBorder.width * 100.f;
        newVolume = std::max(0.f, std::min(100.f, newVolume));
        playerSave.setMusicVolume(newVolume);
        this->_playerData.setMusicVolume(newVolume);
        reloadVolume(newVolume, "music");
    }
    else if (soundSliderBorder.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        newVolume = (mousePosition.x - soundSliderBorder.left) / soundSliderBorder.width * 100.f;
        newVolume = std::max(0.f, std::min(100.f, newVolume));
        playerSave.setSoundVolume(newVolume);
        this->_playerData.setSoundVolume(newVolume);
        reloadVolume(newVolume, "sound");
    }
    if (newVolume == -1)
        return (false);
    else {
        playerSave.savePlayerData(saveFile);
        return (true);
    }
}