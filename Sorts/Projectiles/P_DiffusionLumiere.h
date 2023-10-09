#ifndef P_DIFFUSIONLUMIERE_H
#define P_DIFFUSIONLUMIERE_H

#include "Sorts/Projectiles/Projectile.h"


class P_DiffusionLumiere : public Projectile
{
    Q_OBJECT

public:
    P_DiffusionLumiere(QImage *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double porteeRecu, double posXRecu, double posYRecu, double vitesseXRecu, double vitesseYRecu, double accelXRecu, double accelYRecu);
};

#endif // P_DIFFUSIONLUMIERE_H
