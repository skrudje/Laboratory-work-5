#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <vector>

enum class Move {
    Rock,
    Paper,
    Scissors,
    Lizard,
    Spock
};

// Вспомогательные функции
Move stringToMove(const std::string& s);
std::string moveToString(Move m);
bool beats(Move a, Move b); // true если a побеждает b

#endif