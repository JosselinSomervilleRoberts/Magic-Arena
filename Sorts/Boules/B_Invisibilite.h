#ifndef B_INVISIBILITE_H
#define B_INVISIBILITE_H

#include "Sorts/Boules/Boule.h"


class B_Invisibilite : public Boule
{
    Q_OBJECT

public:
    B_Invisibilite(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu);
};

#endif // B_INVISIBILITE_H
