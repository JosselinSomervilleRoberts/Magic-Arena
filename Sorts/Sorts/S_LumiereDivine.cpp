#include "S_LumiereDivine.h"

S_LumiereDivine::S_LumiereDivine(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;

    coutMana = 500;

    ciblable = false;
    porteeBase = 1;
    dureeCast = 0;
    dureeAction = 3000;
    dureeCooldown = 30000;

    icone = 14;
    buildSprites();
}

void S_LumiereDivine::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/Holy1.wav"));
    player->play();
    Sh_LumiereDivine *shield = new Sh_LumiereDivine(&sprites[0], lanceur, stats, posXPerso, posYPerso);
    emit ajouterAffichable(shield);
    shield->start(seed);
}

void S_LumiereDivine::actionFin()
{}

void S_LumiereDivine::actionDebut()
{}

void S_LumiereDivine::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));
    QImage image1 = QImage("../data/images/animations/Holy5.png");

    for(int y=0; y<4; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites[0].push_back(image1.copy(192*x,192*y,192,192).scaled(48*2,48*2));
        }
    }
    sprites[0].removeFirst();
    sprites[0].removeLast();
    sprites[0].removeLast();

}
