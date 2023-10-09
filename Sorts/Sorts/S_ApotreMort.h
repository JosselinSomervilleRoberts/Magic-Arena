#ifndef S_APOTREMORT_H
#define S_APOTREMORT_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Boules/B_ApotreMort.h"


class S_ApotreMort : public Sort
{
    Q_OBJECT

public:
    S_ApotreMort(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

protected:
    double *posXPerso;
    double *posYPerso;
};

#endif // S_APOTREMORT_H
