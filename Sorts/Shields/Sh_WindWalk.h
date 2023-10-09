#ifndef SH_WINDWALK_H
#define SH_WINDWALK_H


#include "Sorts/Shields/Shield.h"

class Sh_WindWalk : public Shield
{
    Q_OBJECT

public:
    Sh_WindWalk(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu);
};

#endif // SH_WINDWALK_H
