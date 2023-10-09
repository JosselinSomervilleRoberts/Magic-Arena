#ifndef S_EXPLOSIONFEU_H
#define S_EXPLOSIONFEU_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Boules/B_ExplosionFeu.h"
#include "Sorts/Shields/Sh_Feu.h"


class S_ExplosionFeu : public Sort
{
    Q_OBJECT

public:
    S_ExplosionFeu(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu);

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
    Sh_Feu *shield;
    bool isOn;
};

#endif // S_EXPLOSIONFEU_H
