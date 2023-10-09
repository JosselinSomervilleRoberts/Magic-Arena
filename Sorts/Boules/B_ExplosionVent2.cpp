#include "B_ExplosionVent2.h"

B_ExplosionVent2::B_ExplosionVent2(QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu) : Boule(lanceurRecu, collisionRecu, statsPersoRecu, posXRecu, posYRecu)
{
    musique = "../data/musiques/animations/Fire1.ogg";
    tailleX = 2.5;
    tailleY = 2.5;

    hitbox = QRectF(posX-1, posY-1, 2, 2);

    degats[0] = 0; // Dégats Terre Mini
    degats[1] = 0; // Dégats Terre Maxi
    degats[2] = 0; // Dégats Feu Mini
    degats[3] = 0; // Dégats Feu Maxi
    degats[4] = 0; // Dégats Eau Mini
    degats[5] = 0; // Dégats Eau Maxi
    degats[6] = 400; // Dégats Air Mini
    degats[7] = 600; // Dégats Air Maxi

    tauxCrit = 10; // Pourcentage de faire un coup critique
    degatsCrit = 100; // Pourcentage de dégats en plus lors d'un coup critique
    tauxStun = 10; // Pourcentae de stun l'ennemi

    duree = 650;
}

void B_ExplosionVent2::buildSprites()
{
    QImage image = QImage("../data/images/animations/Heal5.png");
    for(int y=0; y<3; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites.push_back(image.copy(192*x,192*y,192,192).scaled(48*tailleX,48*tailleY));
        }
    }
    sprites.removeLast();
    sprites.removeLast();
}
