#include "S_Heal.h"

S_Heal::S_Heal(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;

    coutMana = 250;

    ciblable = false;
    porteeBase = 1;
    dureeCast = 1500;
    dureeAction = 1;
    dureeCooldown = 25000;

    icone = 13;
    buildSprites();
}

void S_Heal::action()
{
    emit ajouterVie(stats->value(0)/5);

    Sh_Heal *shield = new Sh_Heal(&sprites[1], lanceur, stats, posXPerso, posYPerso);
    emit ajouterAffichable(shield);
    shield->start(seed);
}

void S_Heal::actionFin()
{}

void S_Heal::actionDebut()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/Ice4.ogg"));
    player->play();

    B_Heal *boule = new B_Heal(&sprites[0], lanceur, collision, stats, *posXPerso + 0.5, *posYPerso + 0.66);
    emit ajouterAffichable(boule);
    boule->start(seed);
}

void S_Heal::buildSprites()
{
    sprites = QVector<QVector<QImage>>(2,QVector<QImage>(0));
    QImage image = QImage("../data/images/animations/Light7.png");
    for(int y=0; y<6; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites[0].push_back(image.copy(192*x,192*y,192,192).scaled(48*2,48*2));
        }
    }

    QImage image1 = QImage("../data/images/animations/ShieldLight.png");

    for(int y=0; y<4; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites[1].push_back(image1.copy(192*x,192*y,192,192).scaled(48*2,48*2));
        }
    }
}


