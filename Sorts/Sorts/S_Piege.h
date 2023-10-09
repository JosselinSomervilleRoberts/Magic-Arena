#ifndef S_PIEGE_H
#define S_PIEGE_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Projectiles/P_Piege.h"


class S_Piege : public Sort
{
    Q_OBJECT

public:
    S_Piege(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();
};

#endif // S_PIEGE_H
