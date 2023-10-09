#ifndef B_TELEPORTATION_H
#define B_TELEPORTATION_H

#include "Sorts/Boules/Boule.h"

class B_Teleportation : public Boule
{
    Q_OBJECT

public:
    B_Teleportation(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu);
};

#endif // B_TELEPORTATION_H
