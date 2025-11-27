#ifndef RANDOM_PLAYER_H
#define RANDOM_PLAYER_H

#include "Player.h"

class RandomPlayer : public Player {
public:
    explicit RandomPlayer(const std::string& name);
    Move choose() override;
};

#endif