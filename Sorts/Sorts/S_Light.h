#ifndef S_LIGHT_H
#define S_LIGHT_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Boules/B_Light.h"


class S_Light : public Sort
{
    Q_OBJECT

public:
    S_Light(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu);
    ~S_Light();

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

public slots:
    void next();

signals:
    void stun(bool);

protected:
    double *posXPerso;
    double *posYPerso;
    QTimer *timer;
    double rangExterieur;
    double rangInterieur;
};

#endif // S_LIGHT_H
