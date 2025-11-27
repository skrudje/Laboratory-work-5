#ifndef PLAYER_H
#define PLAYER_H

#include "Move.h"
#include <string>

class Player {
public:
    explicit Player(const std::string& name) : name_(name) {}
    virtual ~Player() = default;
    virtual Move choose() = 0;
    std::string getName() const { return name_; }

private:
    std::string name_;
};

#endif