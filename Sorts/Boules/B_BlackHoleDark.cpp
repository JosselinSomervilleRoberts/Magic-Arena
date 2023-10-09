#include "B_BlackHoleDark.h"

B_BlackHoleDark::B_BlackHoleDark(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu) : Boule(spritesRecu, lanceurRecu, collisionRecu, statsPersoRecu, posXRecu, posYRecu)
{
    musique = "../data/musiques/animations/Fire1.ogg";
    tailleX = 4;
    tailleY = 4;

    hitbox = QRectF(posX-1.3, posY-1.3, 2.6, 2.6);

    degats[0] = 1000; // Dégats Terre Mini
    degats[1] = 2800; // Dégats Terre Maxi
    degats[2] = 1000; // Dégats Feu Mini
    degats[3] = 2800; // Dégats Feu Maxi
    degats[4] = 1000; // Dégats Eau Mini
    degats[5] = 2800; // Dégats Eau Maxi
    degats[6] = 1000; // Dégats Air Mini
    degats[7] = 2800; // Dégats Air Maxi

    tauxCrit = 10; // Pourcentage de faire un coup critique
    degatsCrit = 100; // Pourcentage de dégats en plus lors d'un coup critique
    tauxStun = 10; // Pourcentae de stun l'ennemi

    duree = 650;
}
