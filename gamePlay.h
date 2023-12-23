#ifndef GAME_PLAY_H
#define GAME_PLAY_H

#include <thread>  // For std::this_thread::sleep_for
#include <chrono>  // For std::chrono::milliseconds

#include "gameBoard.h"
#include "snake.cpp"
#include "input.cpp"

class GamePlay
{
    private:
        bool gameOver;
        int score;

        GameBoard* board;

    public:
        GamePlay();
        bool getGameOver();
        int getScore();
        void gameLoop();
        void logic();

        //TODO: Add for Nicolas
        /*
                gameOver = true;
                void printGameOver() {
            std::cout << "-----------------\n";
            std::cout << "|   Game Over   |\n";
            std::cout << "-----------------\n";
}
*/

};

#endif // GAME_PLAY_H
