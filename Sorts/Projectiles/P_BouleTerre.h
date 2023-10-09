#ifndef P_BOULETERRE_H
#define P_BOULETERRE_H

#include "Sorts/Projectiles/Projectile.h"


class P_BouleTerre : public Projectile
{
    Q_OBJECT

public:
    P_BouleTerre(QImage *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double porteeRecu, double posXRecu, double posYRecu, double vitesseXRecu, double vitesseYRecu, double accelXRecu, double accelYRecu);
};

#endif // P_BOULETERRE_H
