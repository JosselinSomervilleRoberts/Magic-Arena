#include "S_Piege.h"

S_Piege::S_Piege(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    coutMana = 100;

    ciblable = true;
    porteeBase = 20;
    dureeCast = 350;
    dureeAction = 1;
    dureeCooldown = 12000;

    icone = 4;
    buildSprites();
}

void S_Piege::action()
{
    P_Piege *piege = new P_Piege(&sprites[0][0], lanceur, collision, stats, 0.01, posX, posY, 0.01/6000, 0, 0, 0);
    emit ajouterAffichable(piege);
    piege->start(seed);
}

void S_Piege::actionFin()
{}

void S_Piege::actionDebut()
{}

void S_Piege::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));
    sprites[0].push_back(QImage("../data/images/animations/piege.png").scaled(48*0.85,48*0.85));
}
