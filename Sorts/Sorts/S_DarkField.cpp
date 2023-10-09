#include "S_DarkField.h"

S_DarkField::S_DarkField(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;

    coutMana = 180;

    ciblable = true;
    porteeBase = 20;
    dureeCast = 350;
    dureeAction = 1400;
    dureeCooldown = 8000;

    icone = 8;
    buildSprites();
}

void S_DarkField::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/Dark4.wav"));
    player->play();
    B_DarkField *boule = new B_DarkField(&sprites[0], lanceur, collision, stats, posX, posY-0.5);
    emit ajouterAffichable(boule);
    boule->start(seed);
}

void S_DarkField::actionFin()
{}

void S_DarkField::actionDebut()
{
    Sh_Vampirisme *shield = new Sh_Vampirisme(&sprites[1], lanceur, stats, posXPerso, posYPerso);
    emit ajouterAffichable(shield);
    shield->start(seed);
}

void S_DarkField::buildSprites()
{
    sprites = QVector<QVector<QImage>>(2,QVector<QImage>(0));
    QImage image = QImage("../data/images/animations/StateDown2.png");
    for(int y=0; y<5; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites[0].push_back(image.copy(192*x,192*y,192,192));
        }
    }

    QImage image1 = QImage("../data/images/animations/ShieldDark.png");

    for(int y=0; y<4; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites[1].push_back(image1.copy(192*x,192*y,192,192).scaled(48*4,48*4));
        }
    }
}



