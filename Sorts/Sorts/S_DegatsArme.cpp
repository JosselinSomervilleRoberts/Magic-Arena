#include "S_DegatsArme.h"

S_DegatsArme::S_DegatsArme(Arme *armeRecu, QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu, int *orientationRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
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



void S_DegatsArme::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/Coup.wav"));
    player->play();

    double xBoule, yBoule;
    switch(*orientationPerso)
    {
        case 0: // Haut
        xBoule = *posXPerso -0.05;
        yBoule = *posYPerso - 0.4;
        break;

        case 1: // Gauche
        xBoule = *posXPerso - 0.5;
        yBoule = *posYPerso + 0.137;
        break;

        case 2: // Bas
        xBoule = *posXPerso -0.05;
        yBoule = *posYPerso + 0.6;
        break;

        case 3: // Droite
        xBoule = *posXPerso + 0.4;
        yBoule = *posYPerso + 0.137;
        break;
    }
    B_DegatsArme *boule = new B_DegatsArme(&sprites[0], lanceur, collision, stats, xBoule, yBoule, arme->getDegats(), arme->getTauxCrit(), arme->getDegatsCrit(), arme->getTauxStun());
    emit ajouterAffichable(boule);
    boule->start(seed);
}

void S_DegatsArme::actionFin()
{}

void S_DegatsArme::actionDebut()
{}

void S_DegatsArme::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(1,QImage(0,0)));
    //sprites[0].push_back(QImage(0,0));
}


