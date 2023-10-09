#include "P_BouleEau.h"

P_BouleEau::P_BouleEau(QImage *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double porteeRecu, double posXRecu, double posYRecu, double vitesseXRecu, double vitesseYRecu, double accelXRecu, double accelYRecu) : Projectile(spritesRecu, lanceurRecu, collisionRecu, statsPersoRecu, porteeRecu, posXRecu, posYRecu, vitesseXRecu, vitesseYRecu, accelXRecu, accelYRecu)
{
    hitbox = QRectF(posX - 0.5, posY-0.2, 1, 0.4);

    tailleX = 2;
    tailleY = 2;

    delai = 30;

    passeTerrain = true;
    passeAffichables = false;

    degats[0] = 0;
    degats[1] = 0;
    degats[2] = 2200;
    degats[3] = 3000;
    degats[4] = 0;
    degats[5] = 0;
    degats[6] = 0;
    degats[7] = 0;

    tauxStun = 25;

    calculDegats();
    buildSprites();
}
