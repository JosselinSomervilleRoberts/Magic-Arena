#include "Sorts/Fleche.h"

Fleche::Fleche(Collision *collisionRecu) : Affichable(), collision(collisionRecu)
{
    tailleX = 1;
    tailleY = 1;
    buildSprites();

    connect(timerActualiser, SIGNAL(timeout()), this, SLOT(rafraichir()));
    timerActualiser->start(15);
}


QVector<int> Fleche::getDegats()
{
    return degats;
}

void Fleche::setFleche(double posXRecu, double posYRecu, int xIncrementRecu, int yIncrementRecu, int orientationRecu, QVector<int> degatsRecu, int porteeRecu)
{
    posX = posXRecu;
    posY = posYRecu;
    orientation = orientationRecu;
    degats = degatsRecu;
    portee = porteeRecu;
    xIncrement = xIncrementRecu;
    yIncrement = yIncrementRecu;
    deplacement = 0;
}

void Fleche::rafraichir()
{
    if(deplacement >= portee)
    {
        emit finish(this);
    }
    else
    {
        if(!collision->collisionTerrain(this))
        {
            if(!collision->collisionAffichable(this))
            {
                posX += xIncrement/2.0;
                posY += yIncrement/2.0;
                deplacement += 1/2.0;
                emit besoinRafraichir();
                timerActualiser->start(15);
            }
            else
            {
                emit finish(this);
            }
        }
        else
        {
            emit finish(this);
        }
    }
}

void Fleche::buildSprites()
{
    for(int i=0; i<4; i++)
    {
        sprites[i] = QImage("../data/images/sprites/personnage/fleche_" + QString::number(i) + ".png");
    }
}

QImage Fleche::getSprite()
{
    return sprites[orientation];
}

double Fleche::getPosXAffichage()
{
    return posX;
}

double Fleche::getPosYAffichage()
{
    return posY;
}

QRectF Fleche::getHitbox()
{
    if((orientation == 0) || (orientation == 2))
        return QRectF(posX+0.4, posY+0.1, 0.21, 0.8);
    else
        return QRectF(posX+0.1, posY+0.4, 0.8, 0.21);
}
