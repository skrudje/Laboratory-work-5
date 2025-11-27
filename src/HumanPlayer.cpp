#include "HumanPlayer.h"
#include "Move.h"
#include <iostream>
#include <limits>

using namespace std;

HumanPlayer::HumanPlayer(const string& name) : Player(name) {}

Move HumanPlayer::choose() {
    cout << "\n" << getName() << ", выберите ход:\n";
    cout << "1. Камень\n";
    cout << "2. Бумага\n";
    cout << "3. Ножницы\n";
    cout << "4. Ящерица\n";
    cout << "5. Спок\n";
    cout << "Ваш выбор (1-5): ";

    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 5) {
        cout << "Неверный ввод! Введите число от 1 до 5: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (choice) {
        case 1: return Move::Rock;
        case 2: return Move::Paper;
        case 3: return Move::Scissors;
        case 4: return Move::Lizard;
        case 5: return Move::Spock;
        default: return Move::Rock;
    }
}