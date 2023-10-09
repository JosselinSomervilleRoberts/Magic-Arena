#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H


#include "Arme.h"
#include "Armure.h"

#include <QWidget>
#include <QtSql>

class Equipement : public QObject
{
    Q_OBJECT


public:
    Equipement(QVector<int> vecteurArmesRecu);
    ~Equipement();
    void autoFind(QVector<int> vecteurArmesRecu);
    //void save();
    QVector<Equipable*>* getEquipement() { return vecteurEquipables; }
    Arme *getFirstArme();

public slots:
    //void calculStats();
    void echangerArmes();

    //QVector<int> getStats();

    //void recevoirEquipable(Equipable* equipableRecu);
    //Equipable* getEquipable(int index);
    //void supprimerEquipable(int index);



protected:
    //QVector<int> stats;
    QVector<Equipable*> *vecteurEquipables;
};

#endif // EQUIPEMENT_H
