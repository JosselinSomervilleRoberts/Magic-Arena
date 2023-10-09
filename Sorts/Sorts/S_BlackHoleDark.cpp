#include "S_BlackHoleDark.h"

S_BlackHoleDark::S_BlackHoleDark(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    coutMana = 300;

    ciblable = true;
    porteeBase = 10;
    dureeCast = 350;
    dureeAction = 1400;
    dureeCooldown = 16000;

    icone = 10;
    buildSprites();
}

void S_BlackHoleDark::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/Darkness.wav"));
    player->play();
    B_BlackHoleDark *boule = new B_BlackHoleDark(&sprites[0], lanceur, collision, stats, posX, posY);
    emit ajouterAffichable(boule);
    boule->start(seed);
}

void S_BlackHoleDark::actionFin()
{}

void S_BlackHoleDark::actionDebut()
{}

void S_BlackHoleDark::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));
    QImage image = QImage("../data/images/animations/Darkness1.png");
    for(int r=0; r<2; r++)
    {
        for(int x=0; x<4; x++)
        {
            sprites[0].push_back(image.copy(192*x,0,192,192));
        }
    }

    sprites[0].push_back(image.copy(192*4,0,192,192));
    sprites[0].push_back(image.copy(0,192,192,192));
    sprites[0].push_back(image.copy(192,192,192,192));
    sprites[0].push_back(image.copy(192*2,192,192,192));
    sprites[0].push_back(image.copy(192*3,192,192,192));
}


