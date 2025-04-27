#include <iostream>
#include <string>
#include <stdexcept>

// Базовый класс Game
class Game {
protected:
    bool active;
    std::string gameName;

public:
    // Конструктор Game
    Game(const std::string& name) : active(true), gameName(name) {}

    // Виртуальная функция endGame()
    virtual void endGame() {
        if (!active) {
            throw std::runtime_error("Невозможно завершить неактивную игру.");
        }
        std::cout << "Завершение базовой игры: " << gameName << std::endl;
        active = false;
    }

    // Виртуальный деструктор
    virtual ~Game() {}

    bool isActive() const {
        return active;
    }

    std::string getGameName() const {
        return gameName;
    }
};

// Производный класс ChessGame
class ChessGame : public Game {
private:
    std::string winner;

public:
    // Конструктор ChessGame
    ChessGame(const std::string& name) : Game(name) {}

    // Переопределение функции endGame()
    void endGame() override {
        if (!isActive()) {
            throw std::runtime_error("Невозможно завершить неактивную шахматную партию.");
        }
        std::cout << "Объявление победителя в шахматной партии..." << std::endl;
        // winner = "Player1"; // Например, определяем победителя
        Game::endGame(); // Сначала вызываем базовый endGame()
        std::cout << "Шахматная партия \"" << getGameName() << "\" завершена." << std::endl;
    }
};

// Производный класс FootballGame
class FootballGame : public Game {
private:
    int scoreTeamA;
    int scoreTeamB;

public:
    // Конструктор FootballGame
    FootballGame(const std::string& name) : Game(name), scoreTeamA(0), scoreTeamB(0) {}

    // Переопределение функции endGame()
    void endGame() override {
        if (!isActive()) {
            throw std::runtime_error("Невозможно завершить неактивный футбольный матч.");
        }
        std::cout << "Подсчет очков в футбольном матче..." << std::endl;
        // scoreTeamA = 3; // Например, определяем счет
        // scoreTeamB = 2;
        Game::endGame(); // Сначала вызываем базовый endGame()
        std::cout << "Футбольный матч \"" << getGameName() << "\" завершен со счетом " << scoreTeamA << ":" << scoreTeamB << std::endl;
    }
};

int main() {
    try {
        ChessGame chess("Классическая партия");
        chess.endGame();

        FootballGame football("Чемпионат мира");
        football.endGame();

        // Попытка завершить уже завершенную игру
        football.endGame(); // Выбросит исключение

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}