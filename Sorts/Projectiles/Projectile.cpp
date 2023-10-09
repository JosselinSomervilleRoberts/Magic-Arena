#include "Projectile.h"

Projectile::Projectile(QImage *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double porteeRecu, double posXRecu, double posYRecu, double vitesseXRecu, double vitesseYRecu, double accelXRecu, double accelYRecu) : Affichable()
{
    sprites = spritesRecu;

    doitEtreRafraichi = true;
    lanceur = lanceurRecu;
    fini = false;

    delai = 13;

    degats = QVector<int>(8,0);
    degatsFinaux = QVector<int>(5,0);
    tauxCrit = 0;
    degatsCrit = 0;
    tauxStun = 0;

    collision = collisionRecu;

    posX = posXRecu;
    posY = posYRecu;

    vitesseX = vitesseXRecu;
    vitesseY = vitesseYRecu;
    accelX = accelXRecu;
    accelY = accelYRecu;

    portee = porteeRecu;
    passeAffichables = true;
    passeTerrain = false;

    tailleX = 1;
    tailleY = 1;

    xIncrement = 0;
    yIncrement = 0;

    statsPerso = statsPersoRecu;

    QObject::connect(timerActualiser, SIGNAL(timeout()), this, SLOT(rafraichir()));

    rotateSprite();
    emit addToConsole(Qt::green, "Projectile", "new", true, true);
}

Projectile::~Projectile()
{
    emit addToConsole(Qt::green, "Projectile", "delete", true, true);
}

void Projectile::start(int seedRecu)
{
    qsrand(seedRecu);

    deplacement = 0;
    rafraichir();
}

void Projectile::calculDegats()
{
    degatsFinaux = QVector<int>(0,0);

    for(int i=0; i<4; i++)
    {
        int degatsMin  = degats[2*i] * (1 + double(statsPerso->value(i+5))/100 + double(statsPerso->value(9))/100 );
        int degatsMax  = degats[2*i+1] * (1 + double(statsPerso->value(i+5))/100 + double(statsPerso->value(9))/100 );
        int degatsFait = ((qrand() % (degatsMax - degatsMin + 1)) + degatsMin);

        if(qrand() % 101 <= tauxCrit + statsPerso->value(16))
            degatsFait = degatsFait * (1 + double(degatsCrit + statsPerso->value(15))/100);

        degatsFinaux.push_back(degatsFait);
    }

    if(qrand() % 101 <= tauxStun + statsPerso->value(17))
        degatsFinaux.push_back(1);
    else
        degatsFinaux.push_back(0);
}

void Projectile::collisionDetectee()
{
    if(!passeAffichables)
    {
        fini = true;
        emit colliAffichables();
    }
}

void Projectile::rafraichir()
{
    if(fini)
    {
        emit finish(this);
    }
    else
    {
        if(deplacement >= portee)
        {
            emit finish(this);
        }
        else
        {
            if(!((!passeTerrain) && (collision->collisionTerrain(this))))
            {
                vitesseX += accelX;
                vitesseY += accelY;

                if((accelX != 0) || (accelY != 0))
                    rotateSprite();

                posX += vitesseX;
                posY += vitesseY;
                hitbox.translate(vitesseX, vitesseY);

                deplacement += sqrt(vitesseX*vitesseX + vitesseY*vitesseY);

                collision->collisionAffichable(this);

                if(doitEtreRafraichi)
                    emit besoinRafraichir();

                timerActualiser->start(delai);
            }
            else
            {
                emit colliTerrain();
                emit finish(this);
            }
        }
    }
}

void Projectile::rotateSprite()
{
    double angle = 0;
    if(vitesseX == 0)
    {
        if(vitesseY > 0)
            angle = -90;
        else
            angle = 90;
    }
    else
    {
        angle = qAtan(vitesseY/vitesseX) *180 / 3.14159;
        if(vitesseX < 0)
            angle += 180;
    }

    QTransform t;
    spriteActuel = sprites->transformed(t.rotate(angle));
}


QImage* Projectile::getSprite()
{
    return &spriteActuel;
}

double Projectile::getPosXAffichage()
{
    return posX-tailleX/2.0;
}

double Projectile::getPosYAffichage()
{
    return posY-tailleY/2.0;
}

QRectF Projectile::getHitbox()
{
    return hitbox;
}
