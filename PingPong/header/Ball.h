#ifndef BALL_H
#define BALL_H

#include <raylib.h>
class Ball
{
public:
    Ball();
    Ball(int pos_x, int pos_y, int speed_x, int speed_y, float rad, Color color)
        // Member initialisation list
        : _pos_x(pos_x),
          _pos_y(pos_y),
          _speed_x(speed_x),
          _speed_y(speed_y),
          _rad(rad),
          _color(color){};

    // getters
    int getX() const { return _pos_x; };
    int getY() const { return _pos_y; };
    int getSpeedX() const { return _speed_x; };
    int getSpeedY() const { return _speed_y; };
    float getRad() const { return _rad; };
    Color getColor() const { return _color; };

    // setters
    void setSpeedX(int speed) { _speed_x = speed; };
    void setSpeedY(int speed) { _speed_y = speed; };
    void setX(int pos_x) { _pos_x = pos_x; };
    void setY(int pos_y) { _pos_y = pos_y; };

    // manipulation of ball movements and speed
    void reverseSpeedX() { _speed_x *= -1; }; // Changes the direction the velocity of the X direction by pi
    void reverseSpeedY() { _speed_y *= -1; }; // Changes the direction the velocity of the Y direction by pi
    void reverseSpeed()
    {
        reverseSpeedX();
        reverseSpeedY();
    }

    void incrementSpeedY() { _pos_y += _speed_y; }; // ball position is incremented by the ball speed
    void incrementSpeedX() { _pos_x += _speed_x; };

    void reset(int positionX, int positionY)
    {
        _speed_x = 0;
        _speed_y = 0;
        _pos_x = positionX;
        _pos_y = positionY;
    };

private:
    int _pos_x,
        _pos_y;
    int _speed_x, _speed_y;
    float _rad;
    Color _color;
};
#endif // BALL_H