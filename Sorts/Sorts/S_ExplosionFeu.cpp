#include "S_ExplosionFeu.h"

S_ExplosionFeu::S_ExplosionFeu(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;

    coutMana = 180;

    ciblable = true;
    porteeBase = 20;
    dureeCast = 250;
    dureeAction = 1;
    dureeCooldown = 800;

    icone = 17;
    isOn = false;
    buildSprites();
}

void S_ExplosionFeu::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/Fire1.ogg"));
    player->play();
    emit explosion();
    B_ExplosionFeu *boule = new B_ExplosionFeu(&sprites[0], lanceur, collision, stats, posX, posY);
    emit ajouterAffichable(boule);
    boule->start(seed);
}

void S_ExplosionFeu::actionFin()
{}

void S_ExplosionFeu::actionDebut()
{
    if(!isOn)
    {
        shield = new Sh_Feu(&sprites[1], lanceur, stats, posXPerso, posYPerso);
        emit ajouterAffichable(shield);
        shield->start(seed);
        QObject::connect(shield, SIGNAL(finish(Affichable*)), this, SLOT(shieldOver(Affichable*)));
        isOn = true;
    }
}


void S_ExplosionFeu::stop()
{
    if(isOn)
        shield->end();

    isOn = false;
    this->end();
}

void S_ExplosionFeu::buildSprites()
{
    sprites = QVector<QVector<QImage>>(2,QVector<QImage>(0));
    QImage image1 = QImage("../data/images/animations/Breath.png");
    QImage image2 = QImage("../data/images/animations/Attack2.png");

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

    QImage image3 = QImage("../data/images/animations/ShieldFire.png");

    for(int y=0; y<4; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites[1].push_back(image3.copy(192*x,192*y,192,192).scaled(48*2,48*2));
        }
    }
}


