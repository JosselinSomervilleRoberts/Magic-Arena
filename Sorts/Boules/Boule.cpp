#include "Boule.h"

Boule::Boule(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu) : Affichable()
{
    emit addToConsole(Qt::green, "Boule", "new", true, true);
    sprites = spritesRecu;
    lanceur = lanceurRecu;

    degats = QVector<int>(8,0);
    tauxCrit = 0;
    degatsCrit = 0;
    tauxStun = 0;

    collision = collisionRecu;

    posX = posXRecu;
    posY = posYRecu;

    tailleX = 1;
    tailleY = 1;

    xIncrement = 0;
    yIncrement = 0;

    statsPerso = statsPersoRecu;

    QObject::connect(timerActualiser, SIGNAL(timeout()), this, SLOT(rafraichir()));
}


Boule::~Boule()
{
    emit addToConsole(Qt::green, "Boule", "delete", true, true);
}

void Boule::start(int seedRecu)
{
    qsrand(seedRecu);

    buildSprites();
    etapeMax = sprites->length();
    etape = -1;
    calculDegats();

    rafraichir();
}

void Boule::calculDegats()
{
    degatsFinaux = QVector<int>(0,0);

    for(int i=0; i<4; i++)
    {
        int degatsMin  = degats[2*i] * (1 + double(statsPerso->value(i+5))/100 + double(statsPerso->value(9))/100 );
        int degatsMax  = degats[2*i+1] * (1 + double(statsPerso->value(i+5))/100 + double(statsPerso->value(9))/100 );
        int degatsFait = ((qrand() % (degatsMax - degatsMin + 1)) + degatsMin) / etapeMax;

        if(qrand() % 101 <= tauxCrit + statsPerso->value(16))
            degatsFait = degatsFait * (1 + double(degatsCrit + statsPerso->value(15))/100);

        degatsFinaux.push_back(degatsFait);
    }

    if(qrand() % 101 <= tauxStun + statsPerso->value(17))
        degatsFinaux.push_back(1);
    else
        degatsFinaux.push_back(0);
}

void Boule::rafraichir()
{
    if(etape >= etapeMax - 1)
    {
        emit finish(this);
    }
    else
    {
        etape++;
        collision->collisionAffichable(this);
        emit besoinRafraichir();
        timerActualiser->start(duree/etapeMax);
    }

}



QImage* Boule::getSprite()
{
    return &(sprites->value(etape));
}

double Boule::getPosXAffichage()
{
    return posX-tailleX/2.0;
}

double Boule::getPosYAffichage()
{
    return posY-tailleY/2.0;
}

QRectF Boule::getHitbox()
{
    return hitbox;
}
