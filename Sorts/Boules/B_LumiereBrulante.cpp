#include "B_LumiereBrulante.h"

B_LumiereBrulante::B_LumiereBrulante(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu) : Boule(spritesRecu, lanceurRecu, collisionRecu, statsPersoRecu, posXRecu, posYRecu)
{
    musique = "../data/musiques/animations/Fire1.ogg";
    tailleX = 3.5;
    tailleY = 3.5;

    hitbox = QRectF(posX-1.1, posY-1.1, 2.2, 2.2);

    degats[0] = 0; // Dégats Terre Mini
    degats[1] = 0; // Dégats Terre Maxi
    degats[2] = 1800; // Dégats Feu Mini
    degats[3] = 3000; // Dégats Feu Maxi
    degats[4] = 0; // Dégats Eau Mini
    degats[5] = 0; // Dégats Eau Maxi
    degats[6] = 0; // Dégats Air Mini
    degats[7] = 0; // Dégats Air Maxi

    tauxCrit = 0; // Pourcentage de faire un coup critique
    degatsCrit = 0; // Pourcentage de dégats en plus lors d'un coup critique
    tauxStun = 0; // Pourcentae de stun l'ennemi

    duree = 1100;
}
