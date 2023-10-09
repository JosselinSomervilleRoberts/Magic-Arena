#include "S_LaserEau.h"

S_LaserEau::S_LaserEau(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu, int *orientationRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    qDebug() << "debut laser";
    posXPerso = posXRecu;
    posYPerso = posYRecu;
    orientationPerso = orientationRecu;

    coutMana = 50;

    ciblable = true;
    porteeBase = 15;
    dureeCast = 0;
    dureeAction = 500;
    dureeCooldown = 1000;

    icone = 6;
    buildSprites();

    timer = new QTimer(this);
    timer->setSingleShot(true);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(next()));

    x = 0;
    y = 0;
    qDebug() << "fin laser";
}

S_LaserEau::~S_LaserEau()
{
    delete timer;
}

void S_LaserEau::next()
{
    B_LaserEau *boule = new B_LaserEau(&spritesTournes, lanceur, collision, stats, x, y, *orientationPerso);
    emit ajouterAffichable(boule);
    boule->start(seed);

    nbBoules++;
    if(nbBoules < 3)
        timer->start(50);
}


void S_LaserEau::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/Magic wave 1.wav"));
    player->play();

    nbBoules = 0;
    spritesTournes = sprites[0];

    QTransform t;
    for(int i=0; i<spritesTournes.length(); i++)
    {
        if(*orientationPerso == 0)
        {
            spritesTournes[i] = spritesTournes[i].transformed(t.rotate(180));
            x = *posXPerso + 0.4;
            y = *posYPerso - 3.7;
        }
        else if(*orientationPerso == 1)
        {
            spritesTournes[i] = spritesTournes[i].transformed(t.rotate(90));
            x = *posXPerso - 3.7;
            y = *posYPerso + 0.55;
        }
        else if(*orientationPerso == 2)
        {
            spritesTournes[i] = spritesTournes[i].transformed(t.rotate(0));
            x = *posXPerso + 0.4;
            y = *posYPerso + 4.7;
        }
        else if(*orientationPerso == 3)
        {
            spritesTournes[i] = spritesTournes[i].transformed(t.rotate(270));
            x = *posXPerso + 4.7;
            y = *posYPerso + 0.55;
        }
    }
    next();
}

void S_LaserEau::actionFin()
{}

void S_LaserEau::actionDebut()
{}


void S_LaserEau::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));

    QImage image("../data/images/animations/laser.png");

    for(int i=0; i<8; i++)
    {
        sprites[0].push_back(image.copy(-2+40*i, 0, 40, 157));
    }
}

