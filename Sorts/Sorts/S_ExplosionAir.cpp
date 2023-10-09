#include "S_ExplosionAir.h"

S_ExplosionAir::S_ExplosionAir(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;

    coutMana = 180;

    ciblable = true;
    porteeBase = 20;
    dureeCast = 190;
    dureeAction = 1;
    dureeCooldown = 800;

    icone = 19;
    isOn = false;
    buildSprites();
}

void S_ExplosionAir::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/Thunder1.ogg"));
    player->play();
    emit explosion();
    B_ExplosionVent *boule = new B_ExplosionVent(&sprites[0], lanceur, collision, stats, posX, posY);
    emit ajouterAffichable(boule);
    boule->start(seed);
}

void S_ExplosionAir::actionFin()
{}

void S_ExplosionAir::actionDebut()
{
    if(!isOn)
    {
        shield = new Sh_Air(&sprites[1], lanceur, stats, posXPerso, posYPerso);
        emit ajouterAffichable(shield);
        shield->start(seed);
        isOn = true;
    }
}


void S_ExplosionAir::stop()
{
    if(isOn)
        shield->end();

    isOn = false;
    this->end();
}

void S_ExplosionAir::buildSprites()
{
    sprites = QVector<QVector<QImage>>(2,QVector<QImage>(0));
    QImage image1 = QImage("../data/images/animations/Wind1.png");
    QImage image2 = QImage("../data/images/animations/Attack4.png");

    for(int x=0; x<5; x++)
        sprites[0].push_back(image1.copy(192*x,0,192,192).scaled(48*4,48*4));

    for(int y=1; y<3; y++)
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

    QImage image3 = QImage("../data/images/animations/ShieldWind.png");

    for(int y=0; y<4; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites[1].push_back(image3.copy(192*x,192*y,192,192).scaled(48*2,48*2));
        }
    }
}

