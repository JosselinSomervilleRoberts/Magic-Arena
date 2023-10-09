#include "Sh_Heal.h"

Sh_Heal::Sh_Heal(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu) : Shield(spritesRecu, lanceurRecu, statsPersoRecu, posXRecu, posYRecu)
{
    stats[5] = 30; // Dégats Multi

    dureeAvant = 500;
    dureeShield = 5000;
    dureeApres = 500;

    etapeShield = 9;
}
