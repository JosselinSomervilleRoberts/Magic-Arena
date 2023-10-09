#ifndef SH_AIR_H
#define SH_AIR_H

#include "Sorts/Shields/Shield.h"


class Sh_Air : public Shield
{
    Q_OBJECT

public:
    Sh_Air(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu);
};

#endif // SH_AIR_H
