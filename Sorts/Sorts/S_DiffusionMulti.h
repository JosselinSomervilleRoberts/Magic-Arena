#ifndef S_DIFFUSIONMULTI_H
#define S_DIFFUSIONMULTI_H


#include "Sorts/Sorts/Sort.h"
#include "Sorts/Projectiles/P_BouleFeu.h"
#include "Sorts/Projectiles/P_BouleEau.h"
#include "Sorts/Projectiles/P_BouleAir.h"
#include "Sorts/Projectiles/P_BouleTerre.h"

class S_DiffusionMulti : public Sort
{
    Q_OBJECT

public:
    S_DiffusionMulti(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

protected:
    double *posXPerso;
    double *posYPerso;
};

#endif // S_DIFFUSIONMULTI_H
