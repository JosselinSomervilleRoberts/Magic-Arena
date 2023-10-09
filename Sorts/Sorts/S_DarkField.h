#ifndef S_DARKFIELD_H
#define S_DARKFIELD_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Boules/B_DarkField.h"
#include "Sorts/Shields/Sh_Vampirisme.h"


class S_DarkField : public Sort
{
    Q_OBJECT

public:
    S_DarkField(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

protected:
    double *posXPerso;
    double *posYPerso;
};

#endif
