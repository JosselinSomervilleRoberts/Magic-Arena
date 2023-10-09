#ifndef B_HEAL_H
#define B_HEAL_H

#include "Sorts/Boules/Boule.h"


class B_Heal : public Boule
{
    Q_OBJECT

public:
    B_Heal(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu);
};

#endif // B_HEAL_H
