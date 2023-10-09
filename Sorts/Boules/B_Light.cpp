#include "B_Light.h"

B_Light::B_Light(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu) : Boule(spritesRecu, lanceurRecu, collisionRecu, statsPersoRecu, posXRecu, posYRecu)
{
    musique = "../data/musiques/animations/Fire1.ogg";
    tailleX = 2.5;
    tailleY = 2.5;

    hitbox = QRectF(posX-1.1, posY-1.1, 2.2, 2.2);

    degats[0] = 900; // Dégats Terre Mini
    degats[1] = 1200; // Dégats Terre Maxi
    degats[2] = 900; // Dégats Feu Mini
    degats[3] = 1200; // Dégats Feu Maxi
    degats[4] = 900; // Dégats Eau Mini
    degats[5] = 1200; // Dégats Eau Maxi
    degats[6] = 900; // Dégats Air Mini
    degats[7] = 1200; // Dégats Air Maxi

    tauxCrit = 0; // Pourcentage de faire un coup critique
    degatsCrit = 0; // Pourcentage de dégats en plus lors d'un coup critique
    tauxStun = 10; // Pourcentae de stun l'ennemi

    duree = 200;
}
