#include "B_DarkField.h"

B_DarkField::B_DarkField(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu) : Boule(spritesRecu, lanceurRecu, collisionRecu, statsPersoRecu, posXRecu, posYRecu)
{
    musique = "../data/musiques/animations/Fire1.ogg";
    tailleX = 4;
    tailleY = 4;

    hitbox = QRectF(posX-1.4, posY-0.8, 2.8, 2.65);

    degats[0] = 0; // Dégats Terre Mini
    degats[1] = 0; // Dégats Terre Maxi
    degats[2] = 0; // Dégats Feu Mini
    degats[3] = 0; // Dégats Feu Maxi
    degats[4] = 1100; // Dégats Eau Mini
    degats[5] = 1800; // Dégats Eau Maxi
    degats[6] = 1100; // Dégats Air Mini
    degats[7] = 1800; // Dégats Air Maxi

    tauxCrit = 5; // Pourcentage de faire un coup critique
    degatsCrit = 50; // Pourcentage de dégats en plus lors d'un coup critique
    tauxStun = 50; // Pourcentae de stun l'ennemi

    duree = 750;
}
