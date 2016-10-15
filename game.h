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
    int maxNumber;
    int minNumber;
    int startingGuesses;
    Game();
    Game(int minNum, int maxNum, int guesses);
    int guess(int answer);
    void reset();
    int getGuessesLeft();
    int getNumber();
    bool isOver();
};

#endif // GAME_H
