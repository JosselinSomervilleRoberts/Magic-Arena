#ifndef P_BOULEFEU_H
#define P_BOULEFEU_H

#include "Sorts/Projectiles/Projectile.h"


class P_BouleFeu : public Projectile
{
    Q_OBJECT

public:
    P_BouleFeu(QImage *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double porteeRecu, double posXRecu, double posYRecu, double vitesseXRecu, double vitesseYRecu, double accelXRecu, double accelYRecu);
};

#endif // P_BOULEFEU_H
