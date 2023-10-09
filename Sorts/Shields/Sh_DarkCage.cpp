#include "Sh_DarkCage.h"

Sh_DarkCage::Sh_DarkCage(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu) : Shield(spritesRecu, lanceurRecu, statsPersoRecu, posXRecu, posYRecu)
{
    tailleX = 5;
    tailleY = 5;

    dureeAvant = 600;
    dureeShield = 5000;
    dureeApres = 250;

    etapeShield = 12;
}
