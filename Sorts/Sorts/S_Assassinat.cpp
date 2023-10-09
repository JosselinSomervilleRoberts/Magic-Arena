#include "S_Assassinat.h"

S_Assassinat::S_Assassinat(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu, double *posXRecu, double *posYRecu, int *orientationRecu) : Sort(lanceurRecu, statsRecu, collisionRecu)
{
    posXPerso = posXRecu;
    posYPerso = posYRecu;
    orientationPerso = orientationRecu;

    coutMana = 120;

    ciblable = false;
    porteeBase = 1;
    dureeCast = 0;
    dureeAction = 220;
    dureeCooldown = 6000;

    icone = 1;

    timer = new QTimer(this);
    timer->setSingleShot(true);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(dash()));
    buildSprites();
}

S_Assassinat::~S_Assassinat()
{
    delete timer;
}

void S_Assassinat::action()
{
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/punch2.wav"));
    player->play();
    distance = 0;

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

    projectile = new P_Assassinat(&sprites[0][0], lanceur, collision, stats, 6, *posXPerso + 0.5, *posYPerso + 0.5, vitesseX, vitesseY, 0, 0);
    emit ajouterAffichable(projectile);
    QObject::connect(projectile, SIGNAL(colliTerrain()), this, SLOT(stop()));
    projectile->start(seed);

    dash();
}

void S_Assassinat::dash()
{
        if((distance <= 6) && (isOnAction))
        {
            emit envoyer("p(" + lanceur + "," + QString::number(*posXPerso + vitesseX) + "," + QString::number(*posYPerso + vitesseY) + "," + QString::number(*orientationPerso) + ")");


            timer->start(13);
            distance += sqrt(vitesseX*vitesseX + vitesseY*vitesseY);
        }
}

void S_Assassinat::stop()
{
    *posXPerso = *posXPerso - vitesseX;
    *posYPerso = *posYPerso - vitesseY;
    isOnAction = false;
}

void S_Assassinat::actionFin()
{}

void S_Assassinat::actionDebut()
{}

void S_Assassinat::buildSprites()
{
    sprites = QVector<QVector<QImage>>(1,QVector<QImage>(0));
    sprites[0].push_back(QImage(0,0));
}


