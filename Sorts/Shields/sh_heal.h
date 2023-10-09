#ifndef SH_HEAL_H
#define SH_HEAL_H

#include "Sorts/Shields/Shield.h"


class Sh_Heal : public Shield
{
    Q_OBJECT

public:
    Sh_Heal(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu);
};

#endif // SH_HEAL_H
