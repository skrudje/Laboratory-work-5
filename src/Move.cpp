#include "Move.h"
#include <string>
#include <map>

Move stringToMove(const std::string& s) {
    static std::map<std::string, Move> map = {
        {"Rock", Move::Rock},
        {"Paper", Move::Paper},
        {"Scissors", Move::Scissors},
        {"Lizard", Move::Lizard},
        {"Spock", Move::Spock}
    };
    return map.at(s);
}

std::string moveToString(Move m) {
    switch (m) {
        case Move::Rock:      return "Rock";
        case Move::Paper:     return "Paper";
        case Move::Scissors:  return "Scissors";
        case Move::Lizard:    return "Lizard";
        case Move::Spock:     return "Spock";
        default:              return "Unknown";
    }
}

bool beats(Move a, Move b) {
    // a побеждает b?
    if (a == Move::Scissors && (b == Move::Paper || b == Move::Lizard)) return true;
    if (a == Move::Paper    && (b == Move::Rock  || b == Move::Spock))  return true;
    if (a == Move::Rock     && (b == Move::Lizard || b == Move::Scissors)) return true;
    if (a == Move::Lizard   && (b == Move::Spock || b == Move::Paper))  return true;
    if (a == Move::Spock    && (b == Move::Scissors || b == Move::Rock)) return true;
    return false;
}