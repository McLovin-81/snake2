#include "gamePlay.h"


GamePlay::GamePlay()
{
    gameOver = false;
    board = new GameBoard();
}


void GamePlay::runDirection()
{
    Direction snakeDirection = board->getSnake()->getDirection();
    Direction snakeOldDirection = board->getSnake()->getOldDirection();
    
    if (board->getSnake()->getLength() > 1)
    {
        for (int i = board->getSnake()->getLength() - 1; i > 0; i--)
        {
            board->getSnake()->getCoordinateVector()[i] = board->getSnake()->getCoordinateVector()[i-1];
        }
    }

    switch (snakeDirection)
    {
        case UP:
            if (snakeOldDirection == DOWN)
            {
                board->getSnake()->getCoordinateVector()[0].second++;
            }
            else
            {
                board->getSnake()->getCoordinateVector()[0].second--;
                board->getSnake()->setOldDirection(snakeDirection);
            }
            break;
        case DOWN:
            if (snakeOldDirection == UP)
            {
                board->getSnake()->getCoordinateVector()[0].second--;
            }
            else
            {
                board->getSnake()->getCoordinateVector()[0].second++;
                board->getSnake()->setOldDirection(snakeDirection);
            }
            break;
        case RIGHT:
            if (snakeOldDirection == LEFT)
            {
                board->getSnake()->getCoordinateVector()[0].first--;
            }
            else
            {
                board->getSnake()->getCoordinateVector()[0].first++;
                board->getSnake()->setOldDirection(snakeDirection);
            }
            break;
        case LEFT:
            if (snakeOldDirection == RIGHT)
            {
                board->getSnake()->getCoordinateVector()[0].first++;
            }
            else
            {
                board->getSnake()->getCoordinateVector()[0].first--;
                board->getSnake()->setOldDirection(snakeDirection);
            }
        default:
            break;
    }
}


void GamePlay::gameOverScreen()
{
    std::cout << "-----------------\n";
    std::cout << "|   Game Over   |\n";
    std::cout << "-----------------\n";
}


void GamePlay::collision()
{
    std::vector<std::pair<int, int> > coordinates = board->getSnake()->getCoordinateVector();
    std::pair<int, int> snakeHead = board->getSnake()->getCoordinateVector()[0];
    int snakeLength = board->getSnake()->getLength();

    if (board->getSnake()->getCoordinateVector()[0].first == 0 || board->getSnake()->getCoordinateVector()[0].first == board->getWidth() -1
        || board->getSnake()->getCoordinateVector()[0].second == -1 || board->getSnake()->getCoordinateVector()[0].second == board->getHeight())
    {
        gameOver = true;
    }

    for (int i = 1; i < snakeLength -1; i++)
    {
        if (snakeHead == coordinates[i])
        {
            gameOver = true;
            break;
        }
    }
}


int GamePlay::getRandomNum(int range)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(2, range - 2); // Distribution from 2 to range - 2

    return dis(gen);
}


bool GamePlay::checkIfEaten()
{
    if (board->getSnake()->getCoordinateVector()[0].first == board->getFruit()->getXposition()
        && board->getSnake()->getCoordinateVector()[0].second == board->getFruit()->getYposition())
    {
        return true;
    }
    return false;
}


void GamePlay::doWhenEaten()
{
    board->getFruit()->setXposition(getRandomNum(board->getWidth()));
    board->getFruit()->setYposition(getRandomNum(board->getHeight()));

    board->increaseScore();

    board->getSnake()->setNewCoordinate(board->getSnake()->getCoordinateVector().back().first, board->getSnake()->getCoordinateVector().back().second);
}


void GamePlay::scoreScreen()
{
    std::cout << "-----------------\n";
    std::cout << "   Score: " << board->getScore() << "   \n";
    std::cout << "-----------------\n";
}


void GamePlay::gameLoop()
{
    while (!this->gameOver) // TODO: try do while
    {
        napms(80); // TODO: Put it in another place
        board->draw();
        Input::input(board->getSnake());
        runDirection();
        collision();
        if (checkIfEaten())
        {
            doWhenEaten();
        }
    }
    endwin(); // End ncurses mode from GameBord -> draw

    gameOverScreen();
    scoreScreen();
}
