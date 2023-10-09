#include "P_DiffusionLumiere.h"

P_DiffusionLumiere::P_DiffusionLumiere(QImage *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double porteeRecu, double posXRecu, double posYRecu, double vitesseXRecu, double vitesseYRecu, double accelXRecu, double accelYRecu) : Projectile(spritesRecu, lanceurRecu, collisionRecu, statsPersoRecu, porteeRecu, posXRecu, posYRecu, vitesseXRecu, vitesseYRecu, accelXRecu, accelYRecu)
{
    hitbox = QRectF(posX - 0.5, posY-0.2, 1, 0.4);

    tailleX = 2;
    tailleY = 2;

    passeTerrain = true;
    passeAffichables = false;

    degats[0] = 0;
    degats[1] = 0;
    degats[2] = 0;
    degats[3] = 0;
    degats[4] = 0;
    degats[5] = 0;
    degats[6] = 1200;
    degats[7] = 2000;

    tauxStun = 35;
    tauxCrit = 25;
    degatsCrit = 100;

    calculDegats();
    buildSprites();
}

