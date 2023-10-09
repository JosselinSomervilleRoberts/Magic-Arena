#ifndef B_EXPLOSIONFEU_H
#define B_EXPLOSIONFEU_H

#include "Sorts/Boules/Boule.h"

class B_ExplosionVent2 : public Boule
{
    Q_OBJECT

public:
    B_ExplosionVent2(QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu);
    void buildSprites();
};

#endif // B_TELEPORTATION_H
