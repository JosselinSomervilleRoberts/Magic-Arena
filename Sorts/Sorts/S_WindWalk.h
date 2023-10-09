#ifndef S_WINDWALK_H
#define S_WINDWALK_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Shields/Sh_WindWalk.h"


class S_WindWalk : public Sort
{
    Q_OBJECT

public:
    S_WindWalk(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

protected:
    double *posXPerso;
    double *posYPerso;
};

#endif // S_WINDWALK_H
