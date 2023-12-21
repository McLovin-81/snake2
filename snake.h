#ifndef SNAKE_H
#define SNAKE_H


class Snake
{
    private:
        const char design = 'O';
        int length;

        enum Direction {STOP, UP, DOWN, RIGTH, LEFT};
        Direction direction;

        // Possition. Is that correct here?
        int xPosition;
        int yPosition;

    public:
        Snake();
        void setXposition(int x);
        void setYposition(int y);

        int getXposition();
        int getYposition();

        char getDesign() const;
};


#endif // SNAKE_H
