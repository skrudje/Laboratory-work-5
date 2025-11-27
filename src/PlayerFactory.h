#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include "Player.h"
#include "PlayerType.h"
#include <memory>

class PlayerFactory {
public:
    static std::unique_ptr<Player> createPlayer(PlayerType type, const std::string& name);
};

#endif