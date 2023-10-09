#include "P_Fleche.h"

P_Fleche::P_Fleche(QImage *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double porteeRecu, double posXRecu, double posYRecu, double vitesseXRecu, double vitesseYRecu, double accelXRecu, double accelYRecu, QVector<int> degatsRecu, int tauxCritRecu, int degatsCritRecu, int tauxStunRecu) : Projectile(spritesRecu, lanceurRecu, collisionRecu, statsPersoRecu, porteeRecu, posXRecu, posYRecu, vitesseXRecu, vitesseYRecu, accelXRecu, accelYRecu)
{
    if(vitesseY == 0)
        hitbox = QRectF(posX - 0.4, posY-0.1, 0.8, 0.2);
    else
        hitbox = QRectF(posX - 0.1, posY-0.4, 0.2, 0.8);

    tailleX = 1;
    tailleY = 1;

    passeTerrain = false;
    passeAffichables = false;

    degats = degatsRecu;
    for(int i=0; i<degats.length(); i++)
        degats[i] = degats[i] * 3;

    tauxCrit = tauxCritRecu; // Pourcentage de faire un coup critique
    degatsCrit = degatsCritRecu; // Pourcentage de dégats en plus lors d'un coup critique
    tauxStun = tauxStunRecu; // Pourcentae de stun l'ennemi

    calculDegats();
    buildSprites();
}
