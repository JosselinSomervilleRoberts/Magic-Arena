#ifndef B_LIGHT_H
#define B_LIGHT_H

#include "Sorts/Boules/Boule.h"


class B_Light : public Boule
{
    Q_OBJECT

public:
    B_Light(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu);
};

#endif // B_LIGHT_H
