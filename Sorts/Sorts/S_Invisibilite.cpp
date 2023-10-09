#include "S_Invisibilite.h"

S_Invisibilite::S_Invisibilite(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;

    coutMana = 150;

    ciblable = false;
    porteeBase = 1;
    dureeCast = 651;
    dureeAction = 1;
    dureeCooldown = 20000;

    icone = 2;

    timer = new QTimer(this);
    timer->setSingleShot(true);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(stop()));
    buildSprites();
}

S_Invisibilite::~S_Invisibilite()
{
    delete timer;
}

void S_Invisibilite::stop()
{
    emit setInvisible(false);
}

void S_Invisibilite::action()
{
    emit setInvisible(true);
    timer->start(5000);
}

void S_Invisibilite::actionFin()
{}

void S_Invisibilite::actionDebut()
{
    B_Invisibilite *boule = new B_Invisibilite(&sprites[0], lanceur, collision, stats, *posXPerso+0.5, *posYPerso+0.66);
    emit ajouterAffichable(boule);
    boule->start(seed);
}

void S_Invisibilite::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));
    QImage image = QImage("../data/images/animations/Heal5.png");
    for(int y=0; y<3; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites[0].push_back(image.copy(192*x,192*y,192,192).scaled(48*2,48*2));
        }
    }
    sprites[0].removeLast();
    sprites[0].removeLast();
}
