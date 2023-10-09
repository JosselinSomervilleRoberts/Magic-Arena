#ifndef B_LASEREAU_H
#define B_LASEREAU_H


#include "Sorts/Boules/Boule.h"

class B_LaserEau : public Boule
{
    Q_OBJECT

public:
    B_LaserEau(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu, int orientation);
};

#endif // B_LASEREAU_H
