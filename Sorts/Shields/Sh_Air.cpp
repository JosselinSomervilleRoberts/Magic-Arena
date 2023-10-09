#include "Sh_Air.h"

Sh_Air::Sh_Air(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu) : Shield(spritesRecu, lanceurRecu, statsPersoRecu, posXRecu, posYRecu)
{
    stats[2] = 20; // Vitesse

    dureeAvant = 250;
    dureeShield = -1;
    dureeApres = 500;

    etapeShield = 9;
}

