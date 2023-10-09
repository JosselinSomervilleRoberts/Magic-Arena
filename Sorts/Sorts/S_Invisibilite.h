#ifndef S_INVISIBILITE_H
#define S_INVISIBILITE_H


#include "Sorts/Sorts/Sort.h"
#include "Sorts/Boules/B_Invisibilite.h"

class S_Invisibilite : public Sort
{
    Q_OBJECT

public:
    S_Invisibilite(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu);
    ~S_Invisibilite();

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

public slots:
    void stop();

signals:
    void setInvisible(bool);

protected:
    QTimer *timer;
    double *posXPerso;
    double *posYPerso;
};

#endif // S_INVISIBILITE_H
