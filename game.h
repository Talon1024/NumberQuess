#ifndef GAME_H
#define GAME_H


class Game
{
private:
    int myNumber;
    int guessesLeft;
    int checkAnswer(int answer);
    bool gameOver;
public:
    static const int maxNumber = 10;
    static const int minNumber = 1;
    static const int startingGuesses = 5;
    Game();
    int guess(int answer);
    void reset();
    int getGuessesLeft();
    int getNumber();
    bool isOver();
};

#endif // GAME_H
