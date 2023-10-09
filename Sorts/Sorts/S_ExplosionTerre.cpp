#include "S_ExplosionTerre.h"

S_ExplosionTerre::S_ExplosionTerre(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;

    coutMana = 180;

    ciblable = true;
    porteeBase = 20;
    dureeCast = 250;
    dureeAction = 1;
    dureeCooldown = 800;

    icone = 16;
    isOn = false;
    buildSprites();
}

void S_ExplosionTerre::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/Earth1.ogg"));
    player->play();
    emit explosion();
    B_ExplosionTerre *boule = new B_ExplosionTerre(&sprites[0], lanceur, collision, stats, posX, posY);
    emit ajouterAffichable(boule);
    boule->start(seed);
}


void S_ExplosionTerre::actionFin()
{}

void S_ExplosionTerre::actionDebut()
{
    if(!isOn)
    {
        shield = new Sh_Terre(&sprites[1], lanceur, stats, posXPerso, posYPerso);
        emit ajouterAffichable(shield);
        shield->start(seed);
        isOn = true;
    }
}

void S_ExplosionTerre::stop()
{
    if(isOn)
        shield->end();

    isOn = false;
    this->end();
}

void S_ExplosionTerre::buildSprites()
{
    sprites = QVector<QVector<QImage>>(2,QVector<QImage>(0));
    QImage image1 = QImage("../data/images/animations/Earth1.png");
    QImage image2 = QImage("../data/images/animations/Attack5.png");

    for(int y=0; y<2; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites[0].push_back(image1.copy(192*x,192*y,192,192).scaled(48*4,48*4));
            QPainter paint(&sprites[0][5*y+x]);
            paint.drawImage(0, 0, QImage(image2.copy(192*x,192*y,192,192).scaled(48*4,48*4)));
            paint.end();
        }
    }
    sprites[0].removeLast();
    sprites[0].removeLast();
    sprites[0].removeLast();

    QImage image3 = QImage("../data/images/animations/ShieldTerre.png");

    for(int y=0; y<4; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites[1].push_back(image3.copy(192*x,192*y,192,192).scaled(48*2,48*2));
        }
    }
}

