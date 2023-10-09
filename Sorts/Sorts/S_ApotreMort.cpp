#include "S_ApotreMort.h"

S_ApotreMort::S_ApotreMort(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;

    coutMana = 200;

    ciblable = false;
    porteeBase = 1;
    dureeCast = 0;
    dureeAction = 450;
    dureeCooldown = 14000;

    icone = 5;
    buildSprites();
}

void S_ApotreMort::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/Collapse1.ogg"));
    player->play();
    B_ApotreMort *boule = new B_ApotreMort(&sprites[0], lanceur, collision, stats, *posXPerso+0.4, *posYPerso+0.5);
    emit ajouterAffichable(boule);
    boule->start(seed);
}

void S_ApotreMort::actionFin()
{}

void S_ApotreMort::actionDebut()
{}

void S_ApotreMort::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));
    QImage image = QImage("../data/images/animations/StateDown3.png");
    for(int y=3; y<5; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites[0].push_back(image.copy(192*x,192*y,192,192));
        }
    }
    sprites[0].push_back(image.copy(0,192*5,192,192));
    sprites[0].removeFirst();
}
