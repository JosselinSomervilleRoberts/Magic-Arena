#include "S_LumiereBrulante.h"

S_LumiereBrulante::S_LumiereBrulante(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    coutMana = 200;

    ciblable = true;
    porteeBase = 15;
    dureeCast = 350;
    dureeAction = 1400;
    dureeCooldown = 7000;

    icone = 12;
    buildSprites();
}

void S_LumiereBrulante::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/flash2.wav"));
    player->play();
    B_LumiereBrulante *boule = new B_LumiereBrulante(&sprites[0], lanceur, collision, stats, posX, posY);
    emit ajouterAffichable(boule);
    boule->start(seed);
}

void S_LumiereBrulante::actionFin()
{}

void S_LumiereBrulante::actionDebut()
{}

void S_LumiereBrulante::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));
    QImage image = QImage("../data/images/animations/Recovery3.png");
    for(int y=0; y<5; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites[0].push_back(image.copy(192*x,192*y,192,192).scaled(48*2,48*2));
        }
    }
    sprites[0].removeLast();
    sprites[0].removeLast();
    sprites[0].removeLast();
}

