#include "Sh_Feu.h"

Sh_Feu::Sh_Feu(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu) : Shield(spritesRecu, lanceurRecu, statsPersoRecu, posXRecu, posYRecu)
{
    stats[9] = 30; // Dégats Multi

    dureeAvant = 250;
    dureeShield = -1;
    dureeApres = 500;

    etapeShield = 9;
}
