#ifndef CASE_H
#define CASE_H


class Case
{
public:
    Case();
    Case(int xRecu, int yRecu);
    Case(int xRecu, int yRecu, int accesRecu);

    bool operator==(const Case& case1) const
    {
        if((case1.getX() == this->getX()) && (case1.getY() == this->getY()))
            return true;

        return false;
    }

    bool operator!=(const Case& case1) const
    {
        if((case1.getX() == this->getX()) && (case1.getY() == this->getY()))
            return false;

        return true;
    }

    void setAcces       ( int accesRecu )       { acces = accesRecu; }
    void setX           ( int xRecu )           { x = xRecu; }
    void setY           ( int yRecu )           { y = yRecu; }

    int getAcces()      { return acces; }
    int getX()  const   { return x; }
    int getY()  const   { return y; }

private:
    int x, y;
    int acces;
};

#endif // CASE_H
