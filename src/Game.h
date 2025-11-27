#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "MatchHistory.h"
#include "PlayerType.h"
#include "PlayerFactory.h"
#include <vector>
#include <memory>

class Game {
public:
    Game();
    void playRound();
    void showMenu();
    void run();

private:
    std::vector<std::unique_ptr<Player>> players_;
    MatchHistory history_;
};

#endif