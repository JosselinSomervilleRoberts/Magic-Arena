#ifndef B_EXPLOSIONFEU_H
#define B_EXPLOSIONFEU_H

#include "Sorts/Boules/Boule.h"

class B_ExplosionVent : public Boule
{
    Q_OBJECT

public:
    B_ExplosionVent(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu);
};

#endif // B_TELEPORTATION_H
