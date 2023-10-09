#include "B_DarkCage.h"

B_DarkCage::B_DarkCage(QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu) : Boule(lanceurRecu, collisionRecu, statsPersoRecu, posXRecu, posYRecu)
{
    musique = "../data/musiques/animations/Fire1.ogg";
    tailleX = 6;
    tailleY = 6;

    hitbox = QRectF(posX-2.2, posY-2.2, 4.4, 4.4);

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
    tauxStun = 50; // Pourcentae de stun l'ennemi

    duree = 1250;
}

void B_DarkCage::buildSprites()
{
    QImage image = QImage("../data/images/animations/cageDark.png");
    for(int y=0; y<5; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites.push_back(image.copy(192*x,192*y,192,192));
        }
    }
}
