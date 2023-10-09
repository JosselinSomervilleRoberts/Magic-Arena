#ifndef S_PROJECTILEFEU_H
#define S_PROJECTILEFEU_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Projectiles/P_BouleFeu.h"


class S_ProjectileFeu : public Sort
{
    Q_OBJECT

public:
    S_ProjectileFeu(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

protected:
    double *posXPerso;
    double *posYPerso;
};

#endif // S_PROJECTILEFEU_H
