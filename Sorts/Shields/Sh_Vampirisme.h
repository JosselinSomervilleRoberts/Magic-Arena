#ifndef SH_VAMPIRISME_H
#define SH_VAMPIRISME_H

#include "Sorts/Shields/Shield.h"


class Sh_Vampirisme : public Shield
{
    Q_OBJECT

public:
    Sh_Vampirisme(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu);
};


#endif // SH_VAMPIRISME_H
