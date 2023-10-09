#include "B_ApotreMort.h"

B_ApotreMort::B_ApotreMort(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu) : Boule(spritesRecu, lanceurRecu, collisionRecu, statsPersoRecu, posXRecu, posYRecu)
{
    tailleX = 8;
    tailleY = 8;

    hitbox = QRectF(posX-2.8, posY-2.8, 5.6, 5.6);

    degats[0] = 950; // Dégats Terre Mini
    degats[1] = 1450; // Dégats Terre Maxi
    degats[2] = 950; // Dégats Feu Mini
    degats[3] = 1450; // Dégats Feu Maxi
    degats[4] = 950; // Dégats Eau Mini
    degats[5] = 1450; // Dégats Eau Maxi
    degats[6] = 950; // Dégats Air Mini
    degats[7] = 1450; // Dégats Air Maxi

    tauxCrit = 20; // Pourcentage de faire un coup critique
    degatsCrit = 100; // Pourcentage de dégats en plus lors d'un coup critique
    tauxStun = 0; // Pourcentage de stun l'ennemi

    duree = 450;
}
