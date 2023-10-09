#ifndef SH_FEU_H
#define SH_FEU_H


#include "Sorts/Shields/Shield.h"

class Sh_Feu : public Shield
{
    Q_OBJECT

public:
    Sh_Feu(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu);
};

#endif // SH_FEU_H
