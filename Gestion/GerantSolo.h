#ifndef GERANTSOLO_H
#define GERANTSOLO_H

#include "Gestion/Gerant.h"

class GerantSolo : public Gerant
{
    Q_OBJECT

public:
    GerantSolo();

public slots:
    void castSort(QString, int, double, double);
    void attaquer(QString);

    void setPos(QString, double, double, int);
    void setVie(QString, int, bool);
};


#endif // GERANTSOLO_H
