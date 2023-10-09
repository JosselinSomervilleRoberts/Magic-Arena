#include "S_FlecheGlacee.h"

S_FlecheGlacee::S_FlecheGlacee(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu, int *orientationRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;
    orientationPerso = orientationRecu;

    coutMana = 150;

    ciblable = false;
    porteeBase = 1;
    dureeCast = 200;
    dureeAction = 1;
    dureeCooldown = 1000;

    icone = 1;
}

void S_FlecheGlacee::action()
{
    int vitesseX, vitesseY;

    if(*orientationPerso == 0)
    {
        vitesseX = 0;
        vitesseY = -1;
    }
    if(*orientationPerso == 1)
    {
        vitesseX = -1;
        vitesseY = 0;
    }
    if(*orientationPerso == 2)
    {
        vitesseX = 0;
        vitesseY = 1;
    }
    if(*orientationPerso == 3)
    {
        vitesseX = 1;
        vitesseY = 0;
    }

    P_Vampirisme *projectile = new P_Vampirisme(lanceur, collision, stats, 100, *posXPerso + 0.5, *posYPerso + 0.5, 0.4*vitesseX, 0.4*vitesseY, 0, 0);
    emit ajouterAffichable(projectile);
    projectile->start(seed);
}

void S_FlecheGlacee::actionFin()
{}

void S_FlecheGlacee::actionDebut()
{}

void ChangerArme::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));

}


