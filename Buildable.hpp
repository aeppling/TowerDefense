//
// Created by adrie on 30/03/2023.
//

#ifndef UNTITLED1_BUILDABLE_HPP
#define UNTITLED1_BUILDABLE_HPP

class Buildable {
private:
    int     _size;
public:
    Buildable(int size) : _size(size) {};
    ~Buildable() {};

    // GETTER & SETTER
    int getSize() { return(this->_size); };
    void setSize(int size) { this->_size = size; };
};

#endif //UNTITLED1_BUILDABLE_HPP
