#include "Vivants/Vivant.h"

Vivant::Vivant() : Affichable(), stats(18, 0)
{}

bool Vivant::estVivant()
{
    if(vie > 0)
        return true;
    else
        return false;
}


int Vivant::getAction()
{
    return action;
}


void Vivant::stopAttaque()
{
    actionSprite = 1;
    action = -1;
    etape = 0;
}

int Vivant::getOrientation()
{
    return orientation;
}

double Vivant::getEtape()
{
    return etape;
}

void Vivant::deplacer(int deplacementXRecu, int deplacementYRecu, int orientationRecu)
{
    xIncrement = deplacementXRecu;
    yIncrement = deplacementYRecu;
    orientation = orientationRecu;
    action = 1;
    etape = 0;
    timerActualiser->start(50);
}

void Vivant::stopDeplacementX()
{
    if(yIncrement == 0)
        action = -1;
}

void Vivant::stopDeplacementY()
{
    if(xIncrement == 0)
        action = -1;
}


