#include "B_Invisibilite.h"

B_Invisibilite::B_Invisibilite(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu) : Boule(spritesRecu, lanceurRecu, collisionRecu, statsPersoRecu, posXRecu, posYRecu)
{
    tailleX = 2;
    tailleY = 2;

    hitbox = QRectF(posX-0.5, posY-0.5, 1, 1);

    degats[0] = 0; // Dégats Terre Mini
    degats[1] = 0; // Dégats Terre Maxi
    degats[2] = 0; // Dégats Feu Mini
    degats[3] = 0; // Dégats Feu Maxi
    degats[4] = 0; // Dégats Eau Mini
    degats[5] = 0; // Dégats Eau Maxi
    degats[6] = 0; // Dégats Air Mini
    degats[7] = 0; // Dégats Air Maxi

    tauxCrit = 0; // Pourcentage de faire un coup critique
    degatsCrit = 0; // Pourcentage de dégats en plus lors d'un coup critique
    tauxStun = 0; // Pourcentae de stun l'ennemi

    duree = 650;
}

