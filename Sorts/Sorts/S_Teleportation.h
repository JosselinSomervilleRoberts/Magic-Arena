#ifndef S_TELEPORTATION_H
#define S_TELEPORTATION_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Boules/B_Teleportation.h"

class S_Teleportation : public Sort
{
    Q_OBJECT

public:
    S_Teleportation(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

signals:
    void teleporter(double, double, int);

protected:
    double *posXPerso;
    double *posYPerso;
};

#endif // S_TELEPORTATION_H
