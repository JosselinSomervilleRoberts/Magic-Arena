#ifndef SH_DARKCAGE_H
#define SH_DARKCAGE_H

#include "Sorts/Shields/Shield.h"

class Sh_DarkCage : public Shield
{
    Q_OBJECT

public:
    Sh_DarkCage(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu);
};

#endif // SH_DARKCAGE_H
