#ifndef S_HEAL_H
#define S_HEAL_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Boules/B_Heal.h"
#include "Sorts/Shields/Sh_Heal.h"


class S_Heal : public Sort
{
    Q_OBJECT

public:
    S_Heal(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

signals:
    void ajouterVie(int);

protected:
    double *posXPerso;
    double *posYPerso;
};

#endif // S_HEAL_H
