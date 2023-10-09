#ifndef S_FLECHE_H
#define S_FLECHE_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Projectiles/P_Fleche.h"
#include "Equipement/Arme.h"


class S_Fleche : public Sort
{
    Q_OBJECT

public:
    S_Fleche(Arme **armeRecu, QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu, int *orientationRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

protected:
    Arme **arme;
    double *posXPerso;
    double *posYPerso;
    int *orientationPerso;
};

#endif // S_FLECHE_H
