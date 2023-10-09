#include "ChangerArme.h"

ChangerArme::ChangerArme(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    coutMana = 0;

    ciblable = false;
    porteeBase = 0;
    dureeCast = 1;
    dureeAction = 0;
    dureeCooldown = 5000;

    icone = 0;
    buildSprites();
}

void ChangerArme::action()
{
    emit changerArme();
}

void ChangerArme::actionDebut()
{}

void ChangerArme::actionFin()
{}

void ChangerArme::buildSprites()
{
    sprites = QVector<QVector<QImage>>(0,QVector<QImage>(0));
}
