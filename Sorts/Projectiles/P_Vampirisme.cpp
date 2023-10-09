#include "P_Vampirisme.h"

P_Vampirisme::P_Vampirisme(QImage *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double porteeRecu, double posXRecu, double posYRecu, double vitesseXRecu, double vitesseYRecu, double accelXRecu, double accelYRecu) : Projectile(spritesRecu, lanceurRecu, collisionRecu, statsPersoRecu, porteeRecu, posXRecu, posYRecu, vitesseXRecu, vitesseYRecu, accelXRecu, accelYRecu)
{
    hitbox = QRectF(posX - 0.5, posY-0.2, 1, 0.4);

    tailleX = 2;
    tailleY = 2;

    passeTerrain = true;
    passeAffichables = false;

    degats[0] = 500;
    degats[1] = 850;
    degats[2] = 500;
    degats[3] = 850;
    degats[4] = 500;
    degats[5] = 850;
    degats[6] = 500;
    degats[7] = 850;

    tauxStun = 10;
    tauxCrit = 15;
    degatsCrit = 100;

    calculDegats();
    buildSprites();
}

