#include "S_Fleche.h"

S_Fleche::S_Fleche(Arme **armeRecu, QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu, int *orientationRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    arme = armeRecu;
    posXPerso = posXRecu;
    posYPerso = posYRecu;
    orientationPerso = orientationRecu;

    coutMana = 0;

    ciblable = false;
    porteeBase = 1;
    dureeCast = 0;
    dureeAction = 1;
    dureeCooldown = 0;

    icone = 0;

    buildSprites();
}



void S_Fleche::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/Crossbow.ogg"));
    player->play();

    double vitesseX, vitesseY;

    if(*orientationPerso == 0)
    {
        vitesseX = 0;
        vitesseY = -0.5;
    }
    if(*orientationPerso == 1)
    {
        vitesseX = -0.5;
        vitesseY = 0;
    }
    if(*orientationPerso == 2)
    {
        vitesseX = 0;
        vitesseY = 0.5;
    }
    if(*orientationPerso == 3)
    {
        vitesseX = 0.5;
        vitesseY = 0;
    }
    P_Fleche *fleche = new P_Fleche(&sprites[0][0], lanceur, collision, stats, (*arme)->getPortee(), posX+0.5+vitesseX, posY+0.5+vitesseY, vitesseX, vitesseY, 0, 0, (*arme)->getDegats(), (*arme)->getTauxCrit(), (*arme)->getDegatsCrit(), (*arme)->getTauxStun());
    emit ajouterAffichable(fleche);
    fleche->start(seed);
}

void S_Fleche::actionFin()
{}

void S_Fleche::actionDebut()
{}

void S_Fleche::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));
    sprites[0].push_back(QImage("../data/images/animations/fleche.png").scaled(48,48));
}


