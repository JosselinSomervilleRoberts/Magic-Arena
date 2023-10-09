#include "S_Vampirisme.h"

S_Vampirisme::S_Vampirisme(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu, int *vieRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;
    viePerso = vieRecu;

    coutMana = 100;

    ciblable = true;
    porteeBase = 15;
    dureeCast = 0;
    dureeAction = 0;
    dureeCooldown = 1800;

    icone = 6;
    buildSprites();
}

void S_Vampirisme::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/Magic wave 1.wav"));
    player->play();
    double distanceX = posX - (*posXPerso + 0.5);
    double distanceY = posY - (*posYPerso + 0.5);

    double angle = 0;
    if(distanceX == 0)
    {
        if(distanceY > 0)
            angle = -3.14159/2;
        else
            angle = 3.14159/2;
    }
    else
    {
        angle = qAtan(distanceY/distanceX);// * 180 / 3.14159;
        if(distanceX < 0)
            angle += 3.14159;
    }

    P_Vampirisme *projectile1 = new P_Vampirisme(&sprites[0][0], lanceur, collision, stats, 15, *posXPerso + 0.5 + qCos(angle)*0.5, *posYPerso + 0.5 + qSin(angle)*0.5, 0.45*qCos(angle), 0.45*qSin(angle), 0, 0);
    emit ajouterAffichable(projectile1);
    QObject::connect(projectile1, SIGNAL(colliAffichables()), this, SLOT(addLife()));
    projectile1->start(seed);
}

void S_Vampirisme::actionFin()
{}

void S_Vampirisme::actionDebut()
{}

void S_Vampirisme::addLife()
{
    emit ajouterVie(stats->value(0) / 6);
}

void S_Vampirisme::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));
    sprites[0].push_back(QImage("../data/images/animations/boule_dark.png").scaled(48*2,48*2));
}

