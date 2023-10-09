#include "S_Teleportation.h"

S_Teleportation::S_Teleportation(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;
    coutMana = 200;

    ciblable = true;
    porteeBase = 10;
    dureeCast = 700;
    dureeAction = 0;
    dureeCooldown = 12000;
    icone = 7;
    buildSprites();
}

void S_Teleportation::action()
{
    double oldPosX = *posXPerso;
    double oldPosY = *posYPerso;
    emit teleporter(posX-0.4, posY-0.66, 2);

    if((*posXPerso == oldPosX) && (*posYPerso == oldPosY))
        dureeCooldown = 3000;
}

void S_Teleportation::actionDebut()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/Laser1.ogg"));
    player->play();
    QVector<int> degats(4, 0);
    B_Teleportation *boule = new B_Teleportation(&sprites[0], lanceur, collision, stats, posX, posY);
    emit ajouterAffichable(boule);
    boule->start(seed);
}

void S_Teleportation::actionFin()
{
    dureeCooldown = 12000;
}

void S_Teleportation::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));
    QImage image = QImage("../data/images/animations/Special1.png");
    for(int x=0; x<5; x++)
    {
        for(int y=0; y<3; y++)
        {
            sprites[0].push_back(image.copy(192*x,192*y,192,192).scaled(48*1.33,48*1.33));
        }
    }
    sprites[0].removeLast();
}
