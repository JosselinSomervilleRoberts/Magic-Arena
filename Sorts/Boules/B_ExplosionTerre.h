#ifndef B_EXPLOSIONFEU_H
#define B_EXPLOSIONFEU_H

#include "Sorts/Boules/Boule.h"

class B_ExplosionTerre : public Boule
{
    Q_OBJECT

public:
    B_ExplosionTerre(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu);
};

#endif // B_TELEPORTATION_H
