#include "PlayerFactory.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include <memory>
#include <stdexcept>

std::unique_ptr<Player> PlayerFactory::createPlayer(PlayerType type, const std::string& name) {
    switch (type) {
        case PlayerType::Human:
            return std::make_unique<HumanPlayer>(name);
        case PlayerType::Random:
            return std::make_unique<RandomPlayer>(name);
        default:
            throw std::invalid_argument("Неизвестный тип игрока");
    }
}