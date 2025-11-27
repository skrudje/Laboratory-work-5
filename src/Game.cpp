#include "Game.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "Move.h"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

Game::Game() {
    players_.push_back(PlayerFactory::createPlayer(PlayerType::Random, "Bot"));
    players_.push_back(PlayerFactory::createPlayer(PlayerType::Human, "Teacher"));
    players_.push_back(PlayerFactory::createPlayer(PlayerType::Human, "Student"));
    history_.loadFromFile("data/match_history.json");
}

void Game::playRound() {
    cout << "\n=== Начало игры до победителя ===\n";

    while (true) {
        vector<pair<std::string, Move>> moves;
        vector<Move> moveList;

        // Сбор ходов
        for (const auto& player : players_) {
            Move m = player->choose();
            moves.emplace_back(player->getName(), m);
            moveList.push_back(m);
        }

        // Подсчёт побед
        vector<int> wins(3, 0);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (i != j && beats(moveList[i], moveList[j])) {
                    wins[i]++;
                }
            }
        }

        int maxWins = *max_element(wins.begin(), wins.end());
        vector<string> winners;

        if (maxWins == 2) {
            for (int i = 0; i < 3; ++i) {
                if (wins[i] == 2) {
                    winners.push_back(players_[i]->getName());
                }
            }

            // Записываем в историю только при победителе
            history_.addMatch(moves, winners);
            history_.saveToFile("data/match_history.json");

            // Вывод результата
            cout << "\n--- ИТОГОВЫЙ РЕЗУЛЬТАТ ---\n";
            for (size_t i = 0; i < moves.size(); ++i) {
                cout << moves[i].first << " выбрал " << moveToString(moves[i].second) << "\n";
            }
            cout << "Победитель: ";
            for (size_t i = 0; i < winners.size(); ++i) {
                if (i > 0) cout << ", ";
                std::cout << winners[i];
            }
            cout << "!\n";
            cout << "---------------------------\n\n";
            break; // Выход из цикла
        } else {
            // Ничья — сообщаем, но не сохраняем
            cout << "\n--- Ничья! Ещё один раунд... ---\n";
            for (size_t i = 0; i < moves.size(); ++i) {
                cout << moves[i].first << " → " << moveToString(moves[i].second) << "\n";
            }
            cout << "-----------------------------------\n";
            continue;
        }
    }
}

void Game::showMenu() {
    cout << "\n=== Камень, Ножницы, Бумага, Ящерица, Спок ===\n";
    cout << "1. Сыграть раунд\n";
    cout << "2. Показать статистику\n";
    cout << "3. Выход\n";
    cout << "Выберите действие: ";
}

void Game::run() {
    int choice;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                playRound();
                break;
            case 2:
                history_.displayHistory();
                break;
            case 3:
                cout << "\nДо свидания!\n";
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 3);
}