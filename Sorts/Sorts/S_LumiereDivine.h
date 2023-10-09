#ifndef S_LUMIEREDIVINE_H
#define S_LUMIEREDIVINE_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Shields/Sh_LumiereDivine.h"


class S_LumiereDivine : public Sort
{
    Q_OBJECT

public:
    S_LumiereDivine(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

protected:
    double *posXPerso;
    double *posYPerso;
};

#endif // S_LUMIEREDIVINE_H
