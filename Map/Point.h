#ifndef POINT_H
#define POINT_H

struct Point
{
    int x, y;

    bool operator!=(const Point& case1) const
    {
        if((case1.x == this->x) && (case1.y == this->y))
            return false;

        return true;
    }

    bool operator==(const Point& case1) const
    {
        if((case1.x == this->x) && (case1.y == this->y))
            return true;

        return false;
    }
};

#endif // POINT_H
