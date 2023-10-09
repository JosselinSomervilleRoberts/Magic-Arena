#include "Sh_Vampirisme.h"

Sh_Vampirisme::Sh_Vampirisme(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu) : Shield(spritesRecu, lanceurRecu, statsPersoRecu, posXRecu, posYRecu)
{
    stats[14] = 20; // Resistance multi

    dureeAvant = 350;
    dureeShield = 5000;
    dureeApres = 500;

    etapeShield = 9;
}
