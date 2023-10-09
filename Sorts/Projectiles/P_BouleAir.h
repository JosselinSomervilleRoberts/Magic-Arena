#ifndef P_BOULEAIR_H
#define P_BOULEAIR_H

#include "Sorts/Projectiles/Projectile.h"


class P_BouleAir : public Projectile
{
    Q_OBJECT

public:
    P_BouleAir(QImage *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double porteeRecu, double posXRecu, double posYRecu, double vitesseXRecu, double vitesseYRecu, double accelXRecu, double accelYRecu);
};

#endif // P_BOULEAIR_H
