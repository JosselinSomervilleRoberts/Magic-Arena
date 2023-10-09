#ifndef S_EXPLOSIONTERRE_H
#define S_EXPLOSIONTERRE_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Boules/B_ExplosionTerre.h"
#include "Sorts/Shields/Sh_Terre.h"


class S_ExplosionTerre : public Sort
{
    Q_OBJECT

public:
    S_ExplosionTerre(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu);

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
    Sh_Terre *shield;
    bool isOn;
};

#endif // S_EXPLOSIONTERRE_H
