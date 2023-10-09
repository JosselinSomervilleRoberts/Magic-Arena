#ifndef B_EXPLOSIONGLACE_H
#define B_EXPLOSIONGLACE_H

#include "Sorts/Boules/Boule.h"

class B_ExplosionGlace : public Boule
{
    Q_OBJECT

public:
    B_ExplosionGlace(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu);
};

#endif // B_TELEPORTATION_H
