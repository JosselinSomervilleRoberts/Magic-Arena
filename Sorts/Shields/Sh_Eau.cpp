#include "Sh_Eau.h"

Sh_Eau::Sh_Eau(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu) : Shield(spritesRecu, lanceurRecu, statsPersoRecu, posXRecu, posYRecu)
{
    stats[4] = 80; // Regen Mana

    dureeAvant = 250;
    dureeShield = -1;
    dureeApres = 500;

    etapeShield = 9;
}
