#include "S_TempeteElementaire.h"

S_TempeteElementaire::S_TempeteElementaire(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    coutMana = 100;

    ciblable = true;
    porteeBase = 10;
    dureeCast = 700;
    dureeAction = 2500;
    dureeCooldown = 5000;

    icone = 4012;

    timer = new QTimer(this);
    timer->setSingleShot(true);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(ajouterBoule()));
}

S_TempeteElementaire::~S_TempeteElementaire()
{
    delete timer;
}

void S_TempeteElementaire::action()
{
    qsrand(seed);
    nbBoules = 0;
    ajouterBoule();
}

void S_TempeteElementaire::ajouterBoule()
{
    if(nbBoules < 25)
    {
        int i = qrand() % 101;
        int x = qrand() % 101;
        int y = qrand() % 101;

        /*if(i == 0)
        {
            B_ExplosionFeu *boule = new B_ExplosionFeu(lanceur, collision, stats, posX+x, posY+y);
            emit ajouterAffichable(boule);
            boule->start(seed);
        }
        else if(i ==1)
        {
            B_ExplosionAir *boule = new B_ExplosionAir(lanceur, collision, stats, posX+x, posY+y);
            emit ajouterAffichable(boule);
            boule->start(seed);
        }
        else */if(i == 2)
        {
            B_ExplosionGlace *boule1 = new B_ExplosionGlace(lanceur, collision, stats, posX+(double(x)/25.0), posY+(double(y)/25.0));
            emit ajouterAffichable(boule1);
            boule1->start(seed);
        }
        else if(i == 3)
        {
            B_ExplosionTerre *boule2 = new B_ExplosionTerre(lanceur, collision, stats, posX+(double(x)/25.0), posY+(double(y)/25.0));
            emit ajouterAffichable(boule2);
            boule2->start(seed);
        }

        timer->start(100);
        nbBoules++;
    }
}

void S_TempeteElementaire::actionFin()
{}

void S_TempeteElementaire::actionDebut()
{}

void ChangerArme::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));

}


