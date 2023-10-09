#ifndef EFFETSCOLLISION_H
#define EFFETSCOLLISION_H

#include "Affichable.h"
#include "Vivants/Personnage.h"

//#include "Sorts/Sorts/Fleche.h"
#include "Sorts/Boules/Boule.h"
#include "Sorts/Projectiles/Projectile.h"


class EffetsCollision : public QObject
{
    Q_OBJECT

public:
    EffetsCollision();
    void appliquerEffets(Affichable *affichable1, Affichable *affichable2);

public slots:
    void checkEffetsCollision(Affichable *, Affichable *);
};

#endif // EFFETSCOLLISION_H
