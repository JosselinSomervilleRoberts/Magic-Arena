#ifndef B_DEGATSARME_H
#define B_DEGATSARME_H


#include "Sorts/Boules/Boule.h"

class B_DegatsArme : public Boule
{
    Q_OBJECT

public:
    B_DegatsArme(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu, QVector<int> degatsRecu, int tauxCritRecu, int degatsCritRecu, int tauxStunRecu);
};

#endif // B_DEGATSARME_H
