#ifndef B_EXPLOSIONFEU_H
#define B_EXPLOSIONFEU_H

#include "Sorts/Boules/Boule.h"

class B_ExplosionFeu2 : public Boule
{
    Q_OBJECT

public:
    B_ExplosionFeu2(QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu);
    void buildSprites();
};

#endif // B_TELEPORTATION_H
