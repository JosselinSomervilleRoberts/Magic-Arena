#ifndef CHEMIN_H
#define CHEMIN_H

#include <QVector>
#include <QDebug>
#include <QtMath>
#include <QtWidgets>

#include "Map/Point.h"
#include "Map/Map.h"

class Chemin : public QObject
{
public:
    Chemin(Map *mapRecu);
    ~Chemin();

    QVector<Point> trouverVoisins(Point caseRecu);
    Point choisirCase(QVector<Point> voisins);


public slots:
    QVector<Point> findPath(int xDepart, int yDepart, int xArrivee, int yArrivee);


private:
    QVector<Point> chemin;
    QVector<Point> elimine;

    Point depart, arrivee;
    Map *map;
};

#endif // CHEMIN_H
