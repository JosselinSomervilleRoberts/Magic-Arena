#include "Sh_WindWalk.h"

Sh_WindWalk::Sh_WindWalk(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu) : Shield(spritesRecu, lanceurRecu, statsPersoRecu, posXRecu, posYRecu)
{
    offsetX = 0.6;
    offsetY = 1.0;

    tailleX = 0.7;
    tailleY = 0.7;

    stats[2] = 35; // Vitesse

    dureeAvant = 550;
    dureeShield = 4400;
    dureeApres = 550;

    etapeShield = 10;
}
