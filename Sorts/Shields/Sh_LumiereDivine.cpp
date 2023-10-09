#include "Sh_LumiereDivine.h"

Sh_LumiereDivine::Sh_LumiereDivine(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu) : Shield(spritesRecu, lanceurRecu, statsPersoRecu, posXRecu, posYRecu)
{
    offsetX =0;
    offsetY = - 0.1;

    stats[2] = -statsPerso->value(2)/3; // Vitesse
    stats[9] = -30; // Dégats Multi
    stats[14] = 100-statsPerso->value(14); // Resistance Multi

    dureeAvant = 400;
    dureeShield = 2200;
    dureeApres = 400;

    etapeShield = 8;
}
