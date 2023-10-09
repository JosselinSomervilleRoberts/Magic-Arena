#ifndef S_DIFFUSIONLUMIERE_H
#define S_DIFFUSIONLUMIERE_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Projectiles/P_DiffusionLumiere.h"


class S_DiffusionLumiere : public Sort
{
    Q_OBJECT

public:
    S_DiffusionLumiere(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

protected:
    double *posXPerso;
    double *posYPerso;
};

#endif // S_DIFFUSIONLUMIERE_H
