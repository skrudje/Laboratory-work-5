#include "MatchHistory.h"
#include "Player.h"
#include "Move.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <set>

using json = nlohmann::json;


// Перегружаем для передачи данных явно
void MatchHistory::addMatch(
    const std::vector<std::pair<std::string, Move>>& playerMoves,
    const std::vector<std::string>& winners
) {
    MatchRecord record;
    record.roundId = nextRoundId_++;
    for (const auto& pm : playerMoves) {
        record.players.push_back({pm.first, moveToString(pm.second)});
    }
    record.winners = winners;
    history_.push_back(record);
}

void MatchHistory::saveToFile(const std::string& filename) {
    json j = json::array();
    for (const auto& rec : history_) {
        json playersJson = json::array();
        for (const auto& p : rec.players) {
            playersJson.push_back({{"name", p.name}, {"move", p.move}});
        }
        std::string winnerStr = rec.winners.empty() ? "Draw" : "";
        if (!rec.winners.empty()) {
            for (size_t i = 0; i < rec.winners.size(); ++i) {
                if (i > 0) winnerStr += ",";
                winnerStr += rec.winners[i];
            }
        }
        j.push_back({
            {"round_id", rec.roundId},
            {"players", playersJson},
            {"winner", winnerStr}
        });
    }
    std::ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
    }
}

void MatchHistory::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    try {
        json j;
        file >> j;
        history_.clear();
        nextRoundId_ = 1;
        for (const auto& rec : j) {
            MatchRecord r;
            r.roundId = rec.at("round_id");
            if (r.roundId >= nextRoundId_) nextRoundId_ = r.roundId + 1;
            for (const auto& p : rec.at("players")) {
                r.players.push_back({p.at("name"), p.at("move")});
            }
            std::string winnerStr = rec.at("winner");
            r.winners.clear();
            if (winnerStr != "Draw" && !winnerStr.empty()) {
                size_t start = 0, end;
                while ((end = winnerStr.find(',', start)) != std::string::npos) {
                    r.winners.push_back(winnerStr.substr(start, end - start));
                    start = end + 1;
                }
                r.winners.push_back(winnerStr.substr(start));
            }
            history_.push_back(r);
        }
    } catch (...) {
        std::cerr << "Ошибка чтения истории. Файл повреждён или несовместим.\n";
    }
}

void MatchHistory::displayHistory() const {
    if (history_.empty()) {
        std::cout << "История игр пуста.\n";
        return;
    }
    std::cout << "\n=== История матчей ===\n";
    for (const auto& rec : history_) {
        std::cout << "Раунд #" << rec.roundId << ":\n";
        for (const auto& p : rec.players) {
            std::cout << "  " << p.name << " → " << p.move << "\n";
        }
        if (rec.winners.empty() || rec.winners[0] == "Draw") {
            std::cout << "  Победитель: Ничья\n";
        } else {
            std::cout << "  Победитель: ";
            for (size_t i = 0; i < rec.winners.size(); ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << rec.winners[i];
            }
            std::cout << "\n";
        }
        std::cout << "----------------------\n";
    }
}