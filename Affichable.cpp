#include "Affichable.h"

Affichable::Affichable() : QObject()
{
    exist = 1;

    xIncrement = 0;
    yIncrement = 0;

    timerActualiser = new QTimer(this);
    timerActualiser->setSingleShot(true);
}

Affichable::~Affichable()
{
    exist = 0;
    delete timerActualiser;
}

double Affichable::getPosX()
{
    return posX;
}

double Affichable::getPosY()
{
    return posY;
}

double Affichable::getTailleX()
{
    return tailleX;
}

double Affichable::getTailleY()
{
    return tailleY;
}

int Affichable::getIncrementX()
{
    return xIncrement;
}

int Affichable::getIncrementY()
{
    return yIncrement;
}
