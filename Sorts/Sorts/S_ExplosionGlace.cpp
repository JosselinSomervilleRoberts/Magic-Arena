#include "S_ExplosionGlace.h"

S_ExplosionGlace::S_ExplosionGlace(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;

    coutMana = 130;

    ciblable = true;
    porteeBase = 20;
    dureeCast = 250;
    dureeAction = 1;
    dureeCooldown = 800;

    icone = 18;
    isOn = false;
    buildSprites();
}

void S_ExplosionGlace::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/Cold7.wav"));
    player->play();
    emit explosion();
    B_ExplosionGlace *boule = new B_ExplosionGlace(&sprites[0], lanceur, collision, stats, posX, posY);
    emit ajouterAffichable(boule);
    boule->start(seed);
}

void S_ExplosionGlace::actionFin()
{}


void S_ExplosionGlace::actionDebut()
{
    if(!isOn)
    {
        shield = new Sh_Eau(&sprites[1], lanceur, stats, posXPerso, posYPerso);
        emit ajouterAffichable(shield);
        shield->start(seed);
        isOn = true;
    }
}

void S_ExplosionGlace::stop()
{
    if(isOn)
        shield->end();

    isOn = false;
    this->end();
}

void S_ExplosionGlace::buildSprites()
{
    sprites = QVector<QVector<QImage>>(2,QVector<QImage>(0));
    QImage image = QImage("../data/images/animations/Ice2.png");
    sprites[0].push_back(image.copy(192*4,0,192,192).scaled(48*4,48*4));

    for(int y=1; y<2; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites[0].push_back(image.copy(192*x,192*y,192,192).scaled(48*4,48*4));
        }
    }
    sprites[0].push_back(image.copy(0,0,192,192).scaled(48*4,48*4));
    sprites[0].push_back(image.copy(192,0,192,192).scaled(48*4,48*4));
    sprites[0].push_back(image.copy(192*2,0,192,192).scaled(48*4,48*4));

    QImage image1 = QImage("../data/images/animations/ShieldWater.png");

    for(int y=0; y<4; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites[1].push_back(image1.copy(192*x,192*y,192,192).scaled(48*2,48*2));
        }
    }
}

