#ifndef B_LUMIEREBRULANTE_H
#define B_LUMIEREBRULANTE_H

#include "Sorts/Boules/Boule.h"


class B_LumiereBrulante : public Boule
{
    Q_OBJECT

public:
    B_LumiereBrulante(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu);
};

#endif // B_LUMIEREBRULANTE_H
