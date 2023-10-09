#ifndef SH_LUMIEREDIVINE_H
#define SH_LUMIEREDIVINE_H


#include "Sorts/Shields/Shield.h"

class Sh_LumiereDivine : public Shield
{
    Q_OBJECT

public:
    Sh_LumiereDivine(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu);
};

#endif // SH_LUMIEREDIVINE_H
