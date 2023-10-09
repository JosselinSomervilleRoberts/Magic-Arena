#include "Sh_Terre.h"

Sh_Terre::Sh_Terre(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu) : Shield(spritesRecu, lanceurRecu, statsPersoRecu, posXRecu, posYRecu)
{
    stats[17] = 25; // Taux Stun

    dureeAvant = 250;
    dureeShield = -1;
    dureeApres = 500;

    etapeShield = 9;
}

