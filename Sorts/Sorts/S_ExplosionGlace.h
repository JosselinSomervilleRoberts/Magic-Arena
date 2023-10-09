#ifndef S_EXPLOSIONGLACE_H
#define S_EXPLOSIONGLACE_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Boules/B_ExplosionGlace.h"
#include "Sorts/Shields/Sh_Eau.h"


class S_ExplosionGlace : public Sort
{
    Q_OBJECT

public:
    S_ExplosionGlace(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu);

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
    Sh_Eau *shield;
    bool isOn;
};

#endif // S_EXPLOSIONGLACE_H
