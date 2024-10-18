#ifndef PADDLE_H
#define PADDLE_H
#include <raylib.h>

class Paddle
{
public:
    Paddle(Vector2 p) : _position(p)
    {
        rectangle.x = p.x;
        rectangle.y = p.y;
        rectangle.width = 10;
        rectangle.height = 125;
    };

    Rectangle getRect() const
    {
        return rectangle;
    }

    void moveUP()
    {
        if (rectangle.y <= 0)
            rectangle.y = 0;
        rectangle.y -= 10;
    }

    void moveDown(int WINDOW_HEIGHT)
    {
        if (rectangle.y + rectangle.height >= WINDOW_HEIGHT)
            rectangle.y = WINDOW_HEIGHT - rectangle.height;
        rectangle.y += 10;
    }

    // getters
    int getY() { return rectangle.y; }
    int getHeight() { return rectangle.height; }

    // setters
    void setY(int y) { rectangle.y = y; }

private:
    Vector2 _position;
    Vector2 _velocity;
    Rectangle rectangle = {};
};
#endif // PADDLE_H
