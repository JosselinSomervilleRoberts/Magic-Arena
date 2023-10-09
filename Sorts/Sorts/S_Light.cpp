#include "S_Light.h"

S_Light::S_Light(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;

    coutMana = 400;

    ciblable = false;
    porteeBase = 1;
    dureeCast = 500;
    dureeAction = 1000;
    dureeCooldown = 20000;

    icone = 15;

    timer = new QTimer(this);
    timer->setSingleShot(true);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(next()));
    buildSprites();
}

S_Light::~S_Light()
{
    delete timer;
}

void S_Light::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/Explosion6.wav"));
    player->play();
    emit stun(true);
    rangExterieur = 1;
    rangInterieur = 0;
    next();
}

void S_Light::actionFin()
{}

void S_Light::actionDebut()
{}

void S_Light::next()
{
    double ajoutX = 1 * (rangExterieur + (rangInterieur/(4+2*rangExterieur))) * cos((3.14159*2/(4+2*rangExterieur))*rangInterieur);
    double ajoutY = 1 * (rangExterieur + (rangInterieur/(4+2*rangExterieur))) * sin((3.14159*2/(4+2*rangExterieur))*rangInterieur);
    B_Light *boule = new B_Light(&sprites[0], lanceur, collision, stats, *posXPerso+0.4 + ajoutX, *posYPerso+0.5 + ajoutY);
    emit ajouterAffichable(boule);
    boule->start(seed);

    rangInterieur++;
    if(rangInterieur >= (4+2*rangExterieur))
    {
        rangInterieur = 0;
        rangExterieur++;

        if(!(rangExterieur > 3))
            timer->start(300/(4+2*rangExterieur));
    }
    else
        timer->start(300/(4+2*rangExterieur));
}

void S_Light::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));
    QImage image = QImage("../data/images/animations/Fire3.png");
    for(int y=2; y<4; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites[0].push_back(image.copy(192*x,192*y,192,192).scaled(48*2,48*2));
        }
    }
    sprites[0].removeFirst();
    sprites[0].removeFirst();
}
