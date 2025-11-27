#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
public:
    explicit HumanPlayer(const std::string& name);
    Move choose() override;
};

#endif