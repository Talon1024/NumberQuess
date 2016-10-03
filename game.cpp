#include "game.h"
#include <cstdlib>
#include <ctime>

Game::Game()
{
    reset();
}

int Game::checkAnswer(int answer) {
    if (answer > myNumber) {
        return 1;
    } else if (answer < myNumber) {
        return -1;
    } else {
        gameOver = true;
        return 0;
    }
}

int Game::guess(int answer) {
    if (guessesLeft == 0) {
        gameOver = true;
        return -2;
    } else {
        --guessesLeft;
        return checkAnswer(answer);
    }
}

void Game::reset() {
    gameOver = false;
    std::srand(std::time(NULL));
    myNumber = (std::rand() % (maxNumber - minNumber)) + minNumber;
    guessesLeft = startingGuesses;
}

int Game::getGuessesLeft() {
    return guessesLeft;
}

int Game::getNumber() {
    return myNumber;
}

bool Game::isOver() {
    return gameOver;
}
