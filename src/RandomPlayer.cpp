#include "RandomPlayer.h"
#include "Move.h"
#include <random>
#include <vector>

RandomPlayer::RandomPlayer(const std::string& name) : Player(name) {}

Move RandomPlayer::choose() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::vector<Move> moves = {
        Move::Rock, Move::Paper, Move::Scissors, Move::Lizard, Move::Spock
    };
    std::uniform_int_distribution<> dis(0, static_cast<int>(moves.size()) - 1);
    return moves[dis(gen)];
}