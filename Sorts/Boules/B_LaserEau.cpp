#include "B_LaserEau.h"

B_LaserEau::B_LaserEau(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu, int orientation) : Boule(spritesRecu, lanceurRecu, collisionRecu, statsPersoRecu, posXRecu, posYRecu)
{
    if((orientation == 0) || (orientation == 2))
    {
        tailleX = 0.8;
        tailleY = 8;
        hitbox = QRectF(posX-0.15, posY-3.5, 0.3, 7.5);
    }
    else
    {
        tailleX = 8;
        tailleY = 0.8;
        hitbox = QRectF(posX-3.75, posY-0.15, 7.5, 0.3);
    }

    musique = "../data/musiques/animations/Fire1.ogg";

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

    duree = 400;
}
