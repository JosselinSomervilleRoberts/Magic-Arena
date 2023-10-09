#ifndef S_BLACKHOLEDARK_H
#define S_BLACKHOLEDARK_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Boules/B_BlackHoleDark.h"


class S_BlackHoleDark : public Sort
{
    Q_OBJECT

public:
    S_BlackHoleDark(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();
};

#endif // S_BLACKHOLEDARK_H
