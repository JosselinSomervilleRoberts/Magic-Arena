#ifndef CHANGERARME_H
#define CHANGERARME_H

#include "Sorts/Sorts/Sort.h"
#include "Equipement/Arme.h"

class ChangerArme : public Sort
{
    Q_OBJECT

public:
    ChangerArme(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

signals:
    void changerArme();
};

#endif // CHANGERARME_H
