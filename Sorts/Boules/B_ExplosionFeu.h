#ifndef B_EXPLOSIONFEU_H
#define B_EXPLOSIONFEU_H

#include "Sorts/Boules/Boule.h"

class B_ExplosionFeu : public Boule
{
    Q_OBJECT

public:
    B_ExplosionFeu(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu);
};

#endif // B_TELEPORTATION_H
