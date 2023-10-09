#include "Map/Chemin.h"

Chemin::Chemin(Map *mapRecu) : QObject()
{
    map = mapRecu;
}

Chemin::~Chemin()
{}

QVector<Point> Chemin::trouverVoisins(Point caseRecu)
{
    QVector<Point> voisins;
    int x = caseRecu.x;
    int y = caseRecu.y;

    if(x > 0)
    {
        if((map->caseAccessible(x-1, y, -1, 0)) && (!chemin.contains(Point{x-1, y})) && (!elimine.contains(Point{x-1, y})))
            voisins.push_back(Point{x-1, y});
    }

    if(y > 0)
    {
        if((map->caseAccessible(x, y-1, 0, -1)) && (!chemin.contains(Point{x, y-1})) && (!elimine.contains(Point{x, y-1})))
            voisins.push_back(Point{x, y-1});
    }

    if(x < 39)
    {
        if((map->caseAccessible(x+1, y, +1, 0)) && (!chemin.contains(Point{x+1, y})) && (!elimine.contains(Point{x+1, y})))
            voisins.push_back(Point{x+1, y});
    }

    if(y < 20)
    {
        if((map->caseAccessible(x, y+1, 0, +1)) && (!chemin.contains(Point{x, y+1})) && (!elimine.contains(Point{x, y+1})))
            voisins.push_back(Point{x, y+1});
    }
    //qDebug() << "Voisins = " << QString::number(voisins.size());

    return voisins;
}




Point Chemin::choisirCase(QVector<Point> voisins)
{
    int distanceMini = 1000;
    Point caseChoisie;

    int distRel, distCase, distTot;

    for(int i=0; i<voisins.size(); i++)
    {
        if((!elimine.contains(voisins[i])) && (!chemin.contains(voisins[i])))
        {
            distRel = qSqrt(qPow(arrivee.x-voisins[i].x, 2)  +  qPow(arrivee.y-voisins[i].y, 2));
            distCase = chemin.size();
            distTot = distRel + distCase;

            if(distTot < distanceMini)
            {
                distanceMini = distTot;
                caseChoisie = voisins[i];
            }
        }
    }

    return caseChoisie;
}



QVector<Point> Chemin::findPath(int xDepart, int yDepart, int xArrivee, int yArrivee)
{
    Point point;
    point.x = xDepart;
    point.y = yDepart;

    QVector<Point> renvoi;

    if(!((map->caseAccessible(xArrivee, yArrivee, -1, 0)) || (map->caseAccessible(xArrivee, yArrivee, +1, 0)) || (map->caseAccessible(xArrivee, yArrivee, 0, -1)) || (map->caseAccessible(xArrivee, yArrivee, 0, +1))))
        return QVector<Point>();

    arrivee = Point{xArrivee, yArrivee};
    depart = Point{xDepart, yDepart};

    chemin.clear();
    elimine.clear();

    chemin.push_back(depart);

    while(chemin.last() != arrivee)
    {
        QVector<Point> voisins = trouverVoisins(chemin.last());
        while(voisins.size() == 0)
        {
            if(chemin.size() > 1)
            {
                elimine.push_back(chemin.last());
                chemin.removeLast();
                voisins = trouverVoisins(chemin.last());
            }
            else
            {
                qDebug() << "Error Chemin";
                return QVector<Point>();
            }
        }

        Point caseChoisie = choisirCase(voisins);

        Point point;
        point.x = caseChoisie.x - chemin.last().x;
        point.y = caseChoisie.y - chemin.last().y;
        renvoi.push_back(point);

        chemin.push_back(caseChoisie);
    }
    return renvoi;
}
