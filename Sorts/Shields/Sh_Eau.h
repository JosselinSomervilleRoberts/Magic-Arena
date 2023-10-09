#ifndef SH_EAU_H
#define SH_EAU_H

#include "Sorts/Shields/Shield.h"


class Sh_Eau : public Shield
{
    Q_OBJECT

public:
    Sh_Eau(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu);
};

#endif // SH_EAU_H
