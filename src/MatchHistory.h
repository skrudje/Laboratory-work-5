#ifndef MATCH_HISTORY_H
#define MATCH_HISTORY_H

#include "Move.h"
#include <vector>
#include <string>
#include <utility>

class MatchHistory {
public:
    // вектор пар (имя игрока, его ход)
    void addMatch(
        const std::vector<std::pair<std::string, Move>>& playerMoves,
        const std::vector<std::string>& winners
    );
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void displayHistory() const;

private:
    struct MatchRecord {
        int roundId;
        struct PlayerMove {
            std::string name;
            std::string move;
        };
        std::vector<PlayerMove> players;
        std::vector<std::string> winners;
    };

    std::vector<MatchRecord> history_;
    int nextRoundId_ = 1;
};

#endif // MATCH_HISTORY_H