#ifndef S_TEMPETEELEMENTAIRE_H
#define S_TEMPETEELEMENTAIRE_H

#include "Sorts/Sorts/Sort.h"

#include "Sorts/Boules/B_ExplosionTerre.h"

#include "Sorts/Boules/B_ExplosionFeu2.h"

#include "Sorts/Boules/B_ExplosionGlace.h"

//#include "Sorts/Boules/B_ExplosionVent.h"


class S_TempeteElementaire : public Sort
{
    Q_OBJECT

public:
    S_TempeteElementaire(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu);
    ~S_TempeteElementaire();

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

public slots:
    void ajouterBoule();

protected:
    QTimer *timer;
    int nbBoules;
};

#endif // S_TEMPETEELEMENTAIRE_H
