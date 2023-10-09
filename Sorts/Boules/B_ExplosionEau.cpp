#include "B_ExplosionEau.h"

B_ExplosionEau::B_ExplosionEau(QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu) : Boule(lanceurRecu, collisionRecu, statsPersoRecu, posXRecu, posYRecu)
{
    musique = "../data/musiques/animations/Fire1.ogg";
    tailleX = 4;
    tailleY = 4;

    hitbox = QRectF(posX-1.6, posY-1.6, 3.2, 3.2);

    degats[0] = 0; // Dégats Terre Mini
    degats[1] = 0; // Dégats Terre Maxi
    degats[2] = 0; // Dégats Feu Mini
    degats[3] = 0; // Dégats Feu Maxi
    degats[4] = 790; // Dégats Eau Mini
    degats[5] = 1150; // Dégats Eau Maxi
    degats[6] = 0; // Dégats Air Mini
    degats[7] = 0; // Dégats Air Maxi

    tauxCrit = 10; // Pourcentage de faire un coup critique
    degatsCrit = 100; // Pourcentage de dégats en plus lors d'un coup critique
    tauxStun = 0; // Pourcentage de stun l'ennemi

    duree = 750;
}

void B_ExplosionEau::buildSprites()
{
    QImage image = QImage("../data/images/animations/Water1.png");
    for(int y=0; y<3; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites.push_back(image.copy(192*x,192*y,192,192).scaled(48*tailleX,48*tailleY));
        }
    }
}
