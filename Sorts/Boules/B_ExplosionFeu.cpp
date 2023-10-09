#include "B_ExplosionFeu.h"

B_ExplosionFeu::B_ExplosionFeu(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu) : Boule(spritesRecu, lanceurRecu, collisionRecu, statsPersoRecu, posXRecu, posYRecu)
{
    musique = "../data/musiques/animations/Fire1.ogg";
    tailleX = 4;
    tailleY = 4;

    hitbox = QRectF(posX-1.6, posY-1.6, 3.2, 3.2);

    degats[0] = 0; // Dégats Terre Mini
    degats[1] = 0; // Dégats Terre Maxi
    degats[2] = 1200; // Dégats Feu Mini
    degats[3] = 1600; // Dégats Feu Maxi
    degats[4] = 0; // Dégats Eau Mini
    degats[5] = 0; // Dégats Eau Maxi
    degats[6] = 0; // Dégats Air Mini
    degats[7] = 0; // Dégats Air Maxi

    tauxCrit = 10; // Pourcentage de faire un coup critique
    degatsCrit = 200; // Pourcentage de dégats en plus lors d'un coup critique
    tauxStun = 0; // Pourcentae de stun l'ennemi

    duree = 750;
}
