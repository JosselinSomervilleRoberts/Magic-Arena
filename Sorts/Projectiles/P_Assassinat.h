#ifndef P_ASSASSINAT_H
#define P_ASSASSINAT_H

#include "Sorts/Projectiles/Projectile.h"


class P_Assassinat : public Projectile
{
    Q_OBJECT

public:
    P_Assassinat(QImage *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double porteeRecu, double posXRecu, double posYRecu, double vitesseXRecu, double vitesseYRecu, double accelXRecu, double accelYRecu);
};

#endif // P_ASSASSINAT_H
