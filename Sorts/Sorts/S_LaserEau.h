#ifndef S_LASEREAU_H
#define S_LASEREAU_H


#include "Sorts/Sorts/Sort.h"
#include "Sorts/Boules/B_LaserEau.h"


class S_LaserEau : public Sort
{
    Q_OBJECT

public:
    S_LaserEau(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu, int *orientationRecu);
    ~S_LaserEau();

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

public slots:
    void next();

protected:
    QTimer *timer;
    double *posXPerso;
    double *posYPerso;
    int *orientationPerso;
    int nbBoules;
    double x;
    double y;

    QVector<QImage> spritesTournes;
};

#endif // S_LASEREAU_H
