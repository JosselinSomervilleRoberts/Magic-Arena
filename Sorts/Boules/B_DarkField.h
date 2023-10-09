#ifndef B_DARKFIELD_H
#define B_DARKFIELD_H

#include "Sorts/Boules/Boule.h"


class B_DarkField : public Boule
{
    Q_OBJECT

public:
    B_DarkField(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu);
};


#endif // B_DARKFIELD_H
