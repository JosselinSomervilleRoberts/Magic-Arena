#ifndef P_BOULEEAU_H
#define P_BOULEEAU_H

#include "Sorts/Projectiles/Projectile.h"


class P_BouleEau : public Projectile
{
    Q_OBJECT

public:
    P_BouleEau(QImage *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double porteeRecu, double posXRecu, double posYRecu, double vitesseXRecu, double vitesseYRecu, double accelXRecu, double accelYRecu);
};

#endif // P_BOULEEAU_H
