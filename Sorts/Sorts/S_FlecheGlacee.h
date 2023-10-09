#ifndef S_FLECHEGLACEE_H
#define S_FLECHEGLACEE_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Projectiles/P_Vampirisme.h"


class S_FlecheGlacee : public Sort
{
    Q_OBJECT

public:
    S_FlecheGlacee(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu, int *orientationRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

protected:
    double *posXPerso;
    double *posYPerso;
    int *orientationPerso;
};

#endif // S_FLECHEGLACEE_H
