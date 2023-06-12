//
// Created by adrie on 17/04/2023.
//

#ifndef UNTITLED1_TDPLAYER_HPP
#define UNTITLED1_TDPLAYER_HPP

#include <string>

class TDPlayer {
private:
    std::string _name;
    int         _lifeNumber = 0;
    int         _coinNumber = 0;
    int         _totalKill = 0;
public:
    //CONSTRUCT & OVERLOAD
    TDPlayer(std::string name) : _name(name) {};
    ~TDPlayer() {};

    //GETTER & SETTER
    int             getLifeNumber() { return (this->_lifeNumber); };
    int             getCoinNumber() { return (this->_coinNumber); };
    int             getTotalKill() { return (this->_totalKill); };
    std::string     getName() { return (this->_name); };

    void            setLifeNumber(int value) { this->_lifeNumber = value; };
    void            setCoinNumber(int value) { this->_coinNumber = value; };
    void            setTotalKill(int value) { this->_totalKill = value; };
    void            setPlayerName(std::string value) { this->_name = value; };

    void            resetTotalKill() { this->_totalKill = 0; };
    void            looseLife() { this->_lifeNumber--; };
    void            addKill() { this->_totalKill++; };
    void            looseCoin(int toLoose) { this->_coinNumber = this->_coinNumber - toLoose; };
    void            addCoin(int toAdd) { this->_coinNumber = this->_coinNumber + toAdd; };
    void            setCoin(int value) { this->_coinNumber = value; };
};

#endif //UNTITLED1_TDPLAYER_HPP
