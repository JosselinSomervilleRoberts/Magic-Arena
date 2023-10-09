#include "S_DiffusionMulti.h"

S_DiffusionMulti::S_DiffusionMulti(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;

    coutMana = 400;

    ciblable = false;
    porteeBase = 1;
    dureeCast = 0;
    dureeAction = 1;
    dureeCooldown = 20000;

    icone = 20;
    buildSprites();
}

void S_DiffusionMulti::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/explode4.wav"));
    player->play();
    double angle;
    for(int i=0; i<20; i+=4)
    {
        angle = 3.14159 / 10 * i;
        P_BouleTerre *projectile1 = new P_BouleTerre(&sprites[0][0], lanceur, collision, stats, 5, *posXPerso + 0.5 + qCos(angle)*0.5, *posYPerso + 0.5 + qSin(angle)*0.5, 0.25*qCos(angle), 0.25*qSin(angle), 0, 0);
        emit ajouterAffichable(projectile1);
        projectile1->start(seed);

        angle = 3.14159 / 10 * (i+1);
        P_BouleFeu *projectile2 = new P_BouleFeu(&sprites[0][1], lanceur, collision, stats, 5, *posXPerso + 0.5 + qCos(angle)*0.5, *posYPerso + 0.5 + qSin(angle)*0.5, 0.25*qCos(angle), 0.25*qSin(angle), 0, 0);
        emit ajouterAffichable(projectile2);
        projectile2->start(seed);

        angle = 3.14159 / 10 * (i+2);
        P_BouleEau *projectile3 = new P_BouleEau(&sprites[0][2], lanceur, collision, stats, 5, *posXPerso + 0.5 + qCos(angle)*0.5, *posYPerso + 0.5 + qSin(angle)*0.5, 0.25*qCos(angle), 0.25*qSin(angle), 0, 0);
        emit ajouterAffichable(projectile3);
        projectile3->start(seed);

        angle = 3.14159 / 10 * (i+3);
        P_BouleAir *projectile4 = new P_BouleAir(&sprites[0][3], lanceur, collision, stats, 5, *posXPerso + 0.5 + qCos(angle)*0.5, *posYPerso + 0.5 + qSin(angle)*0.5, 0.25*qCos(angle), 0.25*qSin(angle), 0, 0);
        emit ajouterAffichable(projectile4);
        projectile4->start(seed);
    }


}

void S_DiffusionMulti::actionFin()
{}

void S_DiffusionMulti::actionDebut()
{}

void S_DiffusionMulti::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));
    sprites[0].push_back(QImage("../data/images/animations/boule_terre.png").scaled(48*2,48*2));
    sprites[0].push_back(QImage("../data/images/animations/boule_feu.png").scaled(48*2,48*2));
    sprites[0].push_back(QImage("../data/images/animations/boule_eau.png").scaled(48*2,48*2));
    sprites[0].push_back(QImage("../data/images/animations/boule_air.png").scaled(48*2,48*2));
}


