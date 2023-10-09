#include "Sorts/Sorts/Sort.h"

Sort::Sort(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu) : QObject(), collision(collisionRecu), stats(statsRecu)
{
    lanceur = lanceurRecu;
    coutMana = 0;

    isOnCast = false;

    isOnAction = false;
    timerAction = new QTimer(this);
    timerAction->setSingleShot(true);
    QObject::connect(timerAction, SIGNAL(timeout()), this, SLOT(finAction()));

    isOnCooldown = false;
    timerCooldown = new QTimer(this);
    timerCooldown->setSingleShot(true);
    QObject::connect(timerCooldown, SIGNAL(timeout()), this, SLOT(finCooldown()));

    player = new QMediaPlayer(this);
    player->setVolume(50);
}

Sort::~Sort()
{
    delete timerAction;
    delete timerCooldown;
    delete player;
    emit addToConsole(QColor(255,200,0), "Sort", "deleted", true, true);
}

void Sort::end()
{
    isOnCast = false;
    isOnAction = false;


    isOnCooldown = true;
    if(!timerCooldown->isActive())
        timerCooldown->start(dureeCooldown*double(1-(double(stats->value(18))/100)));

    emit addToConsole(QColor(255,200,0), "Sort", "end", true, true);
}

bool Sort::isInRange(int distance)
{
    if(ciblable)
    {
        if(distance <= porteeBase)
            return true;
        else
            return false;
    }
    else
    {
        return true;
    }
    return false;
}

bool Sort::isCiblable()
{
    return ciblable;
}

double Sort::getCooldownRemaining()
{
    return (timerCooldown->remainingTime()/100)/10.0;
}

double Sort::getCooldown()
{
    return (dureeCooldown/100)/10.0;
}

bool Sort::isAvailable()
{
    if((isOnCast) || (isOnCooldown))
        return false;
    else
        return true;
}

void Sort::cast(int seedRecu, double x, double y)
{
    seed = seedRecu;
    isOnCast = true;
    posX = x;
    posY = y;
    actionDebut();

    emit addToConsole(QColor(255,200,0), "Sort", "casted posX = " + QString::number(x) + "   / posY =  " + QString::number(y), true, true);
}

void Sort::finCast()
{
    isOnCast = false;

    isOnAction = true;
    timerAction->start(dureeAction);
    action();

    isOnCooldown = true;
    timerCooldown->start(dureeCooldown*double(1-(double(stats->value(18))/100)));
}

void Sort::finAction()
{
    isOnAction = false;
    actionFin();
}

void Sort::finCooldown()
{
    isOnCooldown = false;
}
