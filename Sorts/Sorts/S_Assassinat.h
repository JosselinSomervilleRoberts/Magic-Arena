#ifndef S_ASSASSINAT_H
#define S_ASSASSINAT_H


#include "Sorts/Sorts/Sort.h"
#include "Sorts/Projectiles/P_Assassinat.h"

class S_Assassinat : public Sort
{
    Q_OBJECT

public:
    S_Assassinat(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu, int *orientationRecu);
    ~S_Assassinat();

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

public slots:
    void dash();
    void stop();


signals:
    void envoyer(QString);

protected:
    P_Assassinat *projectile;
    double distance, vitesseX, vitesseY;

    double *posXPerso;
    double *posYPerso;
    int *orientationPerso;

    QTimer * timer;
};

#endif // S_ASSASSINAT_H

