#ifndef P_VAMPIRISME_H
#define P_VAMPIRISME_H

#include "Sorts/Projectiles/Projectile.h"


class P_Vampirisme : public Projectile
{
    Q_OBJECT

public:
    P_Vampirisme(QImage *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double porteeRecu, double posXRecu, double posYRecu, double vitesseXRecu, double vitesseYRecu, double accelXRecu, double accelYRecu);
};

#endif // P_VAMPIRISME_H
