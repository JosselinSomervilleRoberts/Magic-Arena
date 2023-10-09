#include "Map/Meteo.h"

Meteo::Meteo() : Affichable()
{
    posX = 0;
    posY = 0;
    tailleX = 40;
    tailleY = 21;

    buildSprites();
    actualSprite = 0;
}

void Meteo::buildSprites()
{
    int couleur = 255;
    int largeur = 5;

    for(int j=0; j<30; j++)
    {
        sprites[j] = QImage(1920, 1008, QImage::Format_ARGB32);
        sprites[j].fill(Qt::transparent);
        QPainter paint(&sprites[j]);
        for(int i=0; i<500; i++) // 500 flocons au hasard
        {
            couleur = (qrand() % (255 - 150 + 1)) + 150;
            largeur = (qrand() % (10)) + 1;
            paint.fillRect((qrand() % (1921)), (qrand() % (1009)), largeur, largeur, QBrush(QColor(couleur, couleur, couleur, couleur)));
        }
        paint.end();
    }
}

QImage Meteo::getSprite()
{
    return sprites[actualSprite];
}

void Meteo::rafraichir()
{
    if(actualSprite < 29)
        actualSprite++;
    else
        actualSprite = 0;

    emit besoinRafraichir();
}
