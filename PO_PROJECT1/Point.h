#pragma once

class Point {
public:
    bool operator==(const Point& other) {
        return (x == other.x && y == other.y);
    }
    Point(int x, int y);
    Point();

    void setX(int x);
    void setY(int y);
    int getX();
    int getY();

protected:
    int x;
    int y;
};
