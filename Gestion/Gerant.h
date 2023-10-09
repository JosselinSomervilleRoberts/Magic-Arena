#ifndef GERANT_H
#define GERANT_H

#include <QObject>
#include <QTime>

class Gerant : public QObject
{
    Q_OBJECT

public:
    Gerant();

public slots:
    virtual void castSort(QString, int, double, double) = 0;
    virtual void attaquer(QString) = 0;

    virtual void setPos(QString, double, double, int) = 0;
    virtual void setVie(QString, int, bool) = 0;

signals:
    void signalCastSort(int,QString, int, double, double);
    void signalAttaquer(int,QString);
    void signalSetPos(QString, double, double, int);
    void signalSetVie(QString, int, bool);
};

#endif // GERANT_H
