#ifndef SH_TERRE_H
#define SH_TERRE_H

#include "Sorts/Shields/Shield.h"

class Sh_Terre : public Shield
{
    Q_OBJECT

public:
    Sh_Terre(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu);
};

#endif // SH_TERRE_H
