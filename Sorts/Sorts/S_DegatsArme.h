#ifndef S_DEGATSARME_H
#define S_DEGATSARME_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Boules/B_DegatsArme.h"
#include "Equipement/Arme.h"


class S_DegatsArme : public Sort
{
    Q_OBJECT

public:
    S_DegatsArme(Arme *armeRecu, QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu, int *orientationRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

protected:
    Arme *arme;
    double *posXPerso;
    double *posYPerso;
    int *orientationPerso;
};

#endif // S_DEGATSARME_H

