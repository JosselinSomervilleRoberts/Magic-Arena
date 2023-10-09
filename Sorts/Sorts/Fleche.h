#ifndef FLECHE_H
#define FLECHE_H

#include <QtWidgets>
#include "Affichable.h"
#include "Map/Collision.h"


class Fleche : public Affichable
{
    Q_OBJECT

public:
    Fleche(Collision *collisionRecu);
    void setFleche(double posXRecu, double posYRecu, int xIncrementRecu, int yIncrementRecu, int orientationRecu, QVector<int> degatsRecu, int porteeRecu);
    QVector<int> getDegats();

    void buildSprites();
    QImage getSprite();
    double getPosXAffichage();
    double getPosYAffichage();
    QRectF getHitbox();


public slots:
    void rafraichir();


protected:
    QImage sprites[4];
    int orientation, portee;
    QVector<int> degats;
    double deplacement;
    Collision *collision;
    double vitesseX, vitesseY, accelX, accelY;

};

#endif // FLECHE_H
