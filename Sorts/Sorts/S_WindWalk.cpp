#include "S_WindWalk.h"

S_WindWalk::S_WindWalk(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;

    coutMana = 80;

    ciblable = false;
    porteeBase = 1;
    dureeCast = 0;
    dureeAction = 5500;
    dureeCooldown = 11000;

    icone = 3;
    buildSprites();
}

void S_WindWalk::action()
{
    Sh_WindWalk *shield = new Sh_WindWalk(&sprites[0], lanceur, stats, posXPerso, posYPerso);
    emit ajouterAffichable(shield);
    shield->start(seed);
}

void S_WindWalk::actionFin()
{}

void S_WindWalk::actionDebut()
{}

void S_WindWalk::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));
    QImage image1 = QImage(0);

    for(int y=0; y<5; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites[0].push_back(image1.copy(192*x,192*y,192,192).scaled(48*0.7,48*0.7));
        }
    }
    sprites[0].removeFirst();
    sprites[0].removeLast();
    sprites[0].removeLast();
}
