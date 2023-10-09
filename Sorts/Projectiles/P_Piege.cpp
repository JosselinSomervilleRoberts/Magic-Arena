#include "P_Piege.h"

P_Piege::P_Piege(QImage *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double porteeRecu, double posXRecu, double posYRecu, double vitesseXRecu, double vitesseYRecu, double accelXRecu, double accelYRecu) : Projectile(spritesRecu, lanceurRecu, collisionRecu, statsPersoRecu, porteeRecu, posXRecu, posYRecu, vitesseXRecu, vitesseYRecu, accelXRecu, accelYRecu)
{
    doitEtreRafraichi = false;
    hitbox = QRectF(posX - 0.35, posY-0.2, 0.7, 0.4);

    tailleX = 0.85;
    tailleY = 0.85;

    delai = 100;

    passeTerrain = false;
    passeAffichables = false;

    degats[0] = 4200;
    degats[1] = 5100;
    degats[2] = 0;
    degats[3] = 0;
    degats[4] = 0;
    degats[5] = 0;
    degats[6] = 0;
    degats[7] = 0;

    calculDegats();
    buildSprites();
}

