#include "P_Assassinat.h"

P_Assassinat::P_Assassinat(QImage *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double porteeRecu, double posXRecu, double posYRecu, double vitesseXRecu, double vitesseYRecu, double accelXRecu, double accelYRecu) : Projectile(spritesRecu, lanceurRecu, collisionRecu, statsPersoRecu, porteeRecu, posXRecu, posYRecu, vitesseXRecu, vitesseYRecu, accelXRecu, accelYRecu)
{
    hitbox = QRectF(posX - 0.35, posY-0.3, 0.6, 0.8);

    tailleX = 1;
    tailleY = 1;

    passeTerrain = false;
    passeAffichables = true;

    degats[0] = 0;
    degats[1] = 0;
    degats[2] = 1900;
    degats[3] = 3200;
    degats[4] = 0;
    degats[5] = 0;
    degats[6] = 0;
    degats[7] = 0;

    tauxCrit = 50;
    degatsCrit = 50;
    tauxStun = 20;

    calculDegats();
    buildSprites();
}

