#ifndef S_EXPLOSIONAIR_H
#define S_EXPLOSIONAIR_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Boules/B_ExplosionVent.h"
#include "Sorts/Shields/Sh_Air.h"


class S_ExplosionAir : public Sort
{
    Q_OBJECT

public:
    S_ExplosionAir(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

public slots:
    void stop();

signals:
    void explosion();

protected:
    double *posXPerso;
    double *posYPerso;
    Sh_Air *shield;
    bool isOn;
};

#endif // S_EXPLOSIONAIR_H
