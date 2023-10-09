#include "Shield.h"

Shield::Shield(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu) : Affichable()
{
    sprites = spritesRecu;

    offsetX = 0;
    offsetY = 0;

    dureeAvant = 200;
    dureeShield = 5000;
    dureeApres = 200;

    etapeShield = 0;

    lanceur = lanceurRecu;
    posXPerso = posXRecu;
    posYPerso = posYRecu;

    stats = QVector<int>(18,0);

    tailleX = 2;
    tailleY = 2;

    posX = 0;
    posY = 0;

    xIncrement = 0;
    yIncrement = 0;

    statsPerso = statsPersoRecu;

    QObject::connect(timerActualiser, SIGNAL(timeout()), this, SLOT(rafraichir()));
    emit addToConsole(Qt::green, "Shield", "new", true, true);
}

Shield::~Shield()
{
    emit addToConsole(Qt::green, "Shield", "delete", true, true);
}

void Shield::end()
{
    annulerEffets();
    emit finish(this);
}

void Shield::start(int seedRecu)
{
    qsrand(seedRecu);

    buildSprites();
    etapeMax = sprites->length();
    etape = -1;
    appliquerEffets();

    rafraichir();
}

void Shield::appliquerEffets()
{
    for(int i=0; i<18; i++)
        statsPerso->replace(i, statsPerso->value(i) + stats[i]);
}

void Shield::annulerEffets()
{
    for(int i=0; i<18; i++)
        statsPerso->replace(i, statsPerso->value(i) - stats[i]);
}

void Shield::rafraichir()
{
    if(etape >= etapeMax - 1)
    {
        annulerEffets();
        emit finish(this);
    }
    else
    {
        etape++;
        emit besoinRafraichir();

        if(etape < etapeShield)
            timerActualiser->start(dureeAvant/etapeShield);
        else if(etape == etapeShield)
            timerActualiser->start(dureeShield);
        else
           timerActualiser->start(dureeApres/(etapeMax-etapeShield));
    }
}



QImage* Shield::getSprite()
{
    return &sprites->value(etape);
}

double Shield::getPosXAffichage()
{
    return *posXPerso-0.52+offsetX;
}

double Shield::getPosYAffichage()
{
    return *posYPerso-0.28+offsetY;
}

QRectF Shield::getHitbox()
{
    return QRectF(*posXPerso, *posYPerso, 0.9, 1.2);
}
