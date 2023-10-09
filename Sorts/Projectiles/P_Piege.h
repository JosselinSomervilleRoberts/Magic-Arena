#ifndef P_PIEGE_H
#define P_PIEGE_H

#include "Sorts/Projectiles/Projectile.h"


class P_Piege : public Projectile
{
    Q_OBJECT

public:
    P_Piege(QImage *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double porteeRecu, double posXRecu, double posYRecu, double vitesseXRecu, double vitesseYRecu, double accelXRecu, double accelYRecu);
};

#endif // P_PIEGE_H
