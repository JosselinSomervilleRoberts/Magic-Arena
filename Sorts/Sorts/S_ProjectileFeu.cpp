#include "S_ProjectileFeu.h"

S_ProjectileFeu::S_ProjectileFeu(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;

    coutMana = 150;

    ciblable = true;
    porteeBase = 15;
    dureeCast = 0;
    dureeAction = 1;
    dureeCooldown = 3000;

    icone = 3038;
}

void S_ProjectileFeu::action()
{
    double distanceX = posX - (*posXPerso + 0.5);
    double distanceY = posY - (*posYPerso + 0.5);

    double angle = 0;
    if(distanceX == 0)
    {
        if(distanceY > 0)
            angle = -3.14159/2;
        else
            angle = 3.14159/2;
    }
    else
    {
        angle = qAtan(distanceY/distanceX);// * 180 / 3.14159;
        if(distanceX < 0)
            angle += 3.14159;
    }

    P_BouleFeu *projectile1 = new P_BouleFeu(lanceur, collision, stats, 15, *posXPerso + 0.5 + qCos(angle)*0.5, *posYPerso + 0.5 + qSin(angle)*0.5, 0.25*qCos(angle), 0.25*qSin(angle), 0, 0);
    emit ajouterAffichable(projectile1);
    P_BouleFeu *projectile2 = new P_BouleFeu(lanceur, collision, stats, 15, *posXPerso + 0.5 + qCos(angle+0.15)*0.5, *posYPerso + 0.5 + qSin(angle+0.15)*0.5, 0.25*qCos(angle+0.15), 0.25*qSin(angle+0.15), 0, 0);
    emit ajouterAffichable(projectile2);
    P_BouleFeu *projectile3 = new P_BouleFeu(lanceur, collision, stats, 15, *posXPerso + 0.5 + qCos(angle-0.15)*0.5, *posYPerso + 0.5 + qSin(angle-0.15)*0.5, 0.25*qCos(angle-0.15), 0.25*qSin(angle-0.15), 0, 0);
    emit ajouterAffichable(projectile3);

    projectile1->start(seed);
    projectile2->start(seed);
    projectile3->start(seed);
}

void S_ProjectileFeu::actionFin()
{}

void S_ProjectileFeu::actionDebut()
{}

void ChangerArme::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));

}

