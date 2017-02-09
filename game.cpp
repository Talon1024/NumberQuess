#include "game.h"
#include <cstdlib>
#include <ctime>

Game::Game()
{
    minNumber = 1;
    maxNumber = 10;
    startingGuesses = 5;
    reset();
}

Game::Game(int minNum, int maxNum, int guesses)
{
    minNumber = minNum;
    maxNumber = maxNum;
    startingGuesses = guesses;
    reset();
}

int Game::checkAnswer(int answer) {
    if (answer < minNumber || answer > maxNumber) return 2;
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
    int retval = checkAnswer(answer);
    if (retval != 2) --guessesLeft;
    if (retval == 0) return retval;
    else {
        if (guessesLeft == 0) {
            gameOver = true;
            return -2;
        } else {
            return checkAnswer(answer);
        }
    }
}

void Game::reset() {
    gameOver = false;
    std::srand(std::time(NULL));
    myNumber = (std::rand() % (maxNumber - minNumber + 1)) + minNumber;
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
