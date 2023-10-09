#ifndef GERANTMULTI_H
#define GERANTMULTI_H

#include "Gestion/Gerant.h"
#include "Communication/Communication.h"

class GerantMulti : public Gerant
{
    Q_OBJECT

public:
    GerantMulti(Communication *com);

public slots:
    void castSort(QString, int, double, double);
    void attaquer(QString);

    void setPos(QString, double, double, int);
    void setVie(QString, int, bool);


    void c_castSort(int, QString, int, double, double);
    void c_attaquer(int, QString);
    void c_setPos(QString, double, double, int);
    void c_setVie(QString, int, bool);


private:
    Communication *communication;
};

#endif // GERANTMULTI_H
