#ifndef B_BLACKHOLEDARK_H
#define B_BLACKHOLEDARK_H

#include "Sorts/Boules/Boule.h"

class B_BlackHoleDark : public Boule
{
    Q_OBJECT

public:
    B_BlackHoleDark(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu);
};

#endif // B_BLACKHOLEDARK_H
