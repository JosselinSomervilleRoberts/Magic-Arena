#include "S_DarkCage.h"

S_DarkCage::S_DarkCage(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    coutMana = 250;

    ciblable = true;
    porteeBase = 10;
    dureeCast = 245;
    dureeAction = 5000;
    dureeCooldown = 20000;

    icone = 9;

    timer = new QTimer(this);
    timer->setSingleShot(true);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(next()));
    buildSprites();
}

S_DarkCage::~S_DarkCage()
{
    delete timer;
}

void S_DarkCage::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/casting02.wav"));
    player->play();
    posX -= 2.0;
    posY -= 2.2;

    vecteur = QVector<QRectF>(0, QRectF(0,0,0,0));
    vecteur.push_back(QRectF(posX, posY, 4, 0.01));
    vecteur.push_back(QRectF(posX, posY+4.4, 3, 0.01));
    vecteur.push_back(QRectF(posX, posY, 0.01, 4.4));
    vecteur.push_back(QRectF(posX+4, posY, 0.01, 4.4));


    Sh_DarkCage *shield = new Sh_DarkCage(&sprites[0], lanceur, stats, &posX, &posY);
    emit ajouterAffichable(shield);
    shield->start(seed);

    isOn = false;
    timer->start(600);
}

void S_DarkCage::next()
{
    if(isOn)
    {
        emit remove(vecteur);
        isOn = false;
    }
    else
    {
        emit add(vecteur);
        timer->start(5000);
        isOn = true;
    }
}

void S_DarkCage::actionFin()
{}

void S_DarkCage::actionDebut()
{}

void S_DarkCage::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));
    QImage image1 = QImage("../data/images/animations/cageDark.png");

    for(int y=0; y<4; y++)
    {
        for(int x=0; x<5; x++)
        {
            sprites[0].push_back(image1.copy(192*x,192*y,192,192).scaled(48*6,48*6));
        }
    }
}
