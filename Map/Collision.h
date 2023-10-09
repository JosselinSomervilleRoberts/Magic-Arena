#ifndef COLLISION_H
#define COLLISION_H

#include <QtWidgets>
#include <QVector>

#include "Affichable.h"
#include "Map/Map.h"

class Collision : public QObject
{
    Q_OBJECT

public:
    Collision(QVector<Affichable*> *vecteurAffichablesRecu, Map *mapRecu);

    bool collisionTerrain(Affichable *affichable);
    bool collisionAffichable(Affichable *affichable);

    QVector<Affichable*> *getAffichables() { return vecteurAffichables; }


signals:
    void collisionDeAffichables(Affichable *, Affichable *);
    // Debug
    void addToConsole(QColor couleur, QString source, QString message, bool newLine, bool important);

protected:
    QVector<Affichable*> *vecteurAffichables;
    Map *map;
    QVector<QRectF> *obstacles;
};

#endif // COLLISION_H
