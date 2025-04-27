#include <iostream>
#include <string>
#include <stdexcept>


class Game {
protected:
    std::string name;
    bool isInitialized = false;

public:
    
    Game(const std::string& name) : name(name) {}

    
    virtual void start() {
        if (isInitialized) {
            std::cout << "Игра " << name << " уже запущена." << std::endl;
            return;
        }

        
        if (!canStart()) {
            throw std::runtime_error("Невозможно начать игру " + name + ". Не выполнены необходимые условия.");
        }

        std::cout << "Игра " << name << " начинается." << std::endl;
        isInitialized = true;  
    }

    
    virtual bool canStart() const {
        return true; 
    }

    
    virtual ~Game() {}

    std::string getName() const {
        return name;
    }

    bool getIsInitialized() const {
        return isInitialized;
    }
};


class Chess : public Game {
private:
    bool hasBoard = false;
    bool hasPieces = false;

public:
    // Конструктор Chess
    Chess(const std::string& name) : Game(name) {}

    void setBoard(bool hasBoard) {
        this->hasBoard = hasBoard;
    }

    void setPieces(bool hasPieces) {
        this->hasPieces = hasPieces;
    }

    
    bool canStart() const override {
        return hasBoard && hasPieces; 
    }

    
    void start() override {
        if (!canStart()) {
             throw std::runtime_error("Невозможно начать игру " + name + ". Отсутствует доска или фигуры.");
        }
        Game::start();
        std::cout << "Начинается шахматная партия." << std::endl;

    }
};


class Tennis : public Game {
private:
    bool hasRackets = false;
    bool hasBall = false;

public:
    
    Tennis(const std::string& name) : Game(name) {}

    void setRackets(bool hasRackets) {
        this->hasRackets = hasRackets;
    }

    void setBall(bool hasBall) {
        this->hasBall = hasBall;
    }

    
    bool canStart() const override {
        return hasRackets && hasBall; 
    }

    
    void start() override {
         if (!canStart()) {
             throw std::runtime_error("Невозможно начать игру " + name + ". Отсутствуют ракетки или мяч.");
        }
        Game::start();
        std::cout << "Начинается теннисный матч." << std::endl;
    }
};

int main() {
    try {
        Chess chess("Шахматы");
        chess.setBoard(true);
        chess.setPieces(true);
        chess.start();

        Tennis tennis("Теннис");
        tennis.setRackets(true);
        tennis.setBall(true);
        tennis.start();

        
        Chess invalidChess("Неправильные шахматы");
        invalidChess.setPieces(true);
        invalidChess.start(); 

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}