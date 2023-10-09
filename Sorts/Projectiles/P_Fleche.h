#ifndef P_FLECHE_H
#define P_FLECHE_H

#include "Sorts/Projectiles/Projectile.h"


class P_Fleche : public Projectile
{
    Q_OBJECT

public:
    P_Fleche(QImage *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double porteeRecu, double posXRecu, double posYRecu, double vitesseXRecu, double vitesseYRecu, double accelXRecu, double accelYRecu, QVector<int> degatsRecu, int tauxCritRecu, int degatsCritRecu, int tauxStunRecu);
};

#endif // P_FLECHE_H
