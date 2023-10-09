#include "B_DegatsArme.h"

B_DegatsArme::B_DegatsArme(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu, QVector<int> degatsRecu, int tauxCritRecu, int degatsCritRecu, int tauxStunRecu) : Boule(spritesRecu, lanceurRecu, collisionRecu, statsPersoRecu, posXRecu, posYRecu)
{
    musique = "";
    tailleX = 1;
    tailleY = 1;

    hitbox = QRectF(posX, posY, 1, 1);

    degats = degatsRecu;
    for(int i=0; i<degats.length(); i++)
        degats[i] = degats[i] * 2;

    tauxCrit = tauxCritRecu; // Pourcentage de faire un coup critique
    degatsCrit = degatsCritRecu; // Pourcentage de dégats en plus lors d'un coup critique
    tauxStun = tauxStunRecu; // Pourcentae de stun l'ennemi

    duree = 1;
}
