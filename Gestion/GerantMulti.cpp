#include "GerantMulti.h"

GerantMulti::GerantMulti(Communication *com) : Gerant()
{
    communication = com;
    qsrand(QTime::currentTime().msec());

    QObject::connect(communication, SIGNAL(c_sort(int,QString,int,double,double)), this, SLOT(c_castSort(int,QString,int,double,double)));
    QObject::connect(communication, SIGNAL(c_setPos(QString,double,double, int)), this, SLOT(c_setPos(QString,double,double,int)));
    QObject::connect(communication, SIGNAL(c_setVie(QString, int, bool)), this, SLOT(c_setVie(QString,int,bool)));
    QObject::connect(communication, SIGNAL(c_attaquer(int,QString)), this, SLOT(c_attaquer(int,QString)));
}

void GerantMulti::attaquer(QString nom)
{
    int rand = qrand() % 10001;
    communication->envoyer("a(" + QString::number(rand) + "," + nom + ")");
}

void GerantMulti::castSort(QString nom, int sort, double x, double y)
{
    int rand = qrand() % 10001;
    communication->envoyer("s(" + QString::number(rand) + "," + nom + "," + QString::number(sort) + "," + QString::number(x) + "," + QString::number(y) + ")");
}

void GerantMulti::setPos(QString nom, double x, double y, int orient)
{
    communication->envoyer("p(" + nom + "," + QString::number(x) + "," + QString::number(y) + "," + QString::number(orient) + ")");
}

void GerantMulti::setVie(QString nom, int vie, bool stun)
{
    communication->envoyer("v(" + nom + "," + QString::number(vie) + "," + QString::number(stun) + ")");
}




void GerantMulti::c_attaquer(int rand, QString nom)
{
    emit signalAttaquer(rand, nom);
}

void GerantMulti::c_castSort(int rand, QString nom, int sort, double x, double y)
{
    emit signalCastSort(rand,nom,sort,x,y);
}

void GerantMulti::c_setPos(QString nom, double x, double y, int orient)
{
    emit signalSetPos(nom, x, y, orient);
}

void GerantMulti::c_setVie(QString nom, int vie, bool stun)
{
    emit signalSetVie(nom, vie, stun);
}
