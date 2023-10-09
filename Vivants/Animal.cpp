#include "Animal.h"

Animal::Animal(QString maitreRecu, Collision *collisionRecu, int typeRecu, int posXRecu, int posYRecu) : Affichable()
{
    qsrand(QDateTime::currentDateTime ().toTime_t ());
    couleur = qrand() % 8;

    invisible = false;
    maitre = maitreRecu;

    collision = collisionRecu;
    posX = posXRecu;
    posY = posYRecu;

    posX = 20;

    etape = 0;
    orientation = 2;

    tailleX = 1;
    tailleY = 1;

    type = typeRecu;

    buildSprites();
}

void Animal::setPosition(double posXRecu, double posYRecu, int orientationRecu)
{
    posX = posXRecu;
    posY = posYRecu;

    orientation = orientationRecu;
    if(etape >= 2)
        etape = 0;
    else
        etape+=0.25;
}

void Animal::buildSprites()
{
    QImage image("../data/images/animaux/" + QString::number(type) + ".png");
    double width = image.width();
    double height = image.height();

    if(type < 100)
    {
        width = width / 4;
        height = height / 2;
        if(couleur >= 4)
            image = image.copy((couleur-4) * width,height,width,height);
        else
            image = image.copy((couleur) * width,0,width,height);
    }

    tailleX = width /(3*48);
    tailleY = height /(4*48);


    sprites = QVector<QVector<QImage>>(4, QVector<QImage>(0));
    for(int y=0; y<4; y++)
    {
        for(int x=0; x<3; x++)
            sprites[y].push_back(image.copy(tailleX*48*x, tailleY*48*y, tailleX*48, tailleY*48));
    }
}


QImage* Animal::getSprite()
{
    return &sprites[orientation][etape];
}

double Animal::getPosXAffichage()
{
    return posX-tailleX/2+0.5;
}

double Animal::getPosYAffichage()
{
    return posY-tailleY/2+0.5;
}

QRectF Animal::getHitbox()
{
    if((orientation == 0) || (orientation == 3))
        return QRectF(posX+0.2, posY+0.28,0.8,0.8);
    else
        return QRectF(posX+0.05, posY+0.45,0.8,0.5);
}

void Animal::setInvisible(bool invisibleRecu)
{
    invisible = invisibleRecu;
}

QString Animal::getMaitre()
{
    return maitre;
}
