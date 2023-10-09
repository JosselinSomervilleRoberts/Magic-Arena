#include "GerantSolo.h"

GerantSolo::GerantSolo() : Gerant()
{
    qsrand(QTime::currentTime().msec());
}


void GerantSolo::attaquer(QString nom)
{
    int rand = qrand() % 10001;
    emit signalAttaquer(rand, nom);
}

void GerantSolo::castSort(QString nom, int sort, double x, double y)
{
    int rand = qrand() % 10001;
    emit signalCastSort(rand, nom, sort, x, y);
}

void GerantSolo::setPos(QString nom, double x, double y, int orient)
{
    emit signalSetPos(nom, x, y, orient);
}

void GerantSolo::setVie(QString nom, int vie, bool stun)
{
    signalSetVie(nom, vie, stun);
}

