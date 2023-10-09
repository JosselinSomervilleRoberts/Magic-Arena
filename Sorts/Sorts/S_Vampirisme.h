#ifndef S_VAMPIRISME_H
#define S_VAMPIRISME_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Projectiles/P_Vampirisme.h"


class S_Vampirisme : public Sort
{
    Q_OBJECT

public:
    S_Vampirisme(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu, int *vieRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

public slots:
    void addLife();

signals:
    void ajouterVie(int);

protected:
    double *posXPerso;
    double *posYPerso;
    int *viePerso;
};

#endif // S_VAMPIRISME_H
