#ifndef B_APOTREMORT_H
#define B_APOTREMORT_H

#include "Sorts/Boules/Boule.h"

class B_ApotreMort : public Boule
{
    Q_OBJECT

public:
    B_ApotreMort(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu);
};

#endif // B_APOTREMORT_H
