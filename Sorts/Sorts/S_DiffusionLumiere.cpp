#include "S_DiffusionLumiere.h"

S_DiffusionLumiere::S_DiffusionLumiere(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;

    coutMana = 120;

    ciblable = true;
    porteeBase = 15;
    dureeCast = 0;
    dureeAction = 1;
    dureeCooldown = 4500;

    icone = 11;
    buildSprites();
}

void S_DiffusionLumiere::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/Cold7.wav"));
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

    P_DiffusionLumiere *projectile1 = new P_DiffusionLumiere(&sprites[0][0], lanceur, collision, stats, 15, *posXPerso + 0.5 + qCos(angle)*0.5, *posYPerso + 0.5 + qSin(angle)*0.5, 0.25*qCos(angle), 0.25*qSin(angle), 0, 0);
    emit ajouterAffichable(projectile1);
    P_DiffusionLumiere *projectile2 = new P_DiffusionLumiere(&sprites[0][0], lanceur, collision, stats, 15, *posXPerso + 0.5 + qCos(angle+0.15)*0.5, *posYPerso + 0.5 + qSin(angle+0.15)*0.5, 0.25*qCos(angle+0.15), 0.25*qSin(angle+0.15), 0, 0);
    emit ajouterAffichable(projectile2);
    P_DiffusionLumiere *projectile3 = new P_DiffusionLumiere(&sprites[0][0], lanceur, collision, stats, 15, *posXPerso + 0.5 + qCos(angle-0.15)*0.5, *posYPerso + 0.5 + qSin(angle-0.15)*0.5, 0.25*qCos(angle-0.15), 0.25*qSin(angle-0.15), 0, 0);
    emit ajouterAffichable(projectile3);
    P_DiffusionLumiere *projectile4 = new P_DiffusionLumiere(&sprites[0][0], lanceur, collision, stats, 15, *posXPerso + 0.5 + qCos(angle+0.075)*0.5, *posYPerso + 0.5 + qSin(angle+0.075)*0.5, 0.25*qCos(angle+0.075), 0.25*qSin(angle+0.075), 0, 0);
    emit ajouterAffichable(projectile4);
    P_DiffusionLumiere *projectile5 = new P_DiffusionLumiere(&sprites[0][0], lanceur, collision, stats, 15, *posXPerso + 0.5 + qCos(angle-0.075)*0.5, *posYPerso + 0.5 + qSin(angle-0.075)*0.5, 0.25*qCos(angle-0.075), 0.25*qSin(angle-0.075), 0, 0);
    emit ajouterAffichable(projectile5);

    projectile1->start(seed);
    projectile2->start(seed);
    projectile3->start(seed);
    projectile4->start(seed);
    projectile5->start(seed);
}

void S_DiffusionLumiere::actionFin()
{}

void S_DiffusionLumiere::actionDebut()
{}

void S_DiffusionLumiere::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));
    sprites[0].push_back(QImage("../data/images/animations/boule_light.png").scaled(48*3.5,48*3.5));
}

