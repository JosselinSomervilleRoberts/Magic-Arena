#ifndef S_LUMIEREBRULANTE_H
#define S_LUMIEREBRULANTE_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Boules/B_LumiereBrulante.h"


class S_LumiereBrulante : public Sort
{
    Q_OBJECT

public:
    S_LumiereBrulante(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu);

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();
};

#endif // S_LUMIEREBRULANTE_H
