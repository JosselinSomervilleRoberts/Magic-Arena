#ifndef CONTROLEUR_H
#define CONTROLEUR_H


#include <QObject>

#include "Vivants/Vivant.h"
#include "Vivants/Personnage.h"
#include "Vivants/Animal.h"
#include "Vue.h"
#include "Affichable.h"

#include "Map/Map.h"
#include "Map/Collision.h"
#include "Map/EffetsCollision.h"

#include "Communication/Communication.h"


#include "Vivants/Monstre.h"
#include "Gestion/GerantMulti.h"
#include "Gestion/GerantSolo.h"


class Controleur : public QObject
{
    Q_OBJECT

public:
    Controleur();
    ~Controleur();


public slots:
    void supprimerAffichable(Affichable *);
    void ajouterAffichable(Affichable *);

    void c_sort(int,QString, int, double, double);
    void c_attaquer(int,QString);
    void c_setPos(QString, double, double, int);
    void c_setVie(QString,int,bool);
    void nouveauPerso(QString, int, int, bool);
    void supprimerPerso(QString);

    virtual void lancerPartie() = 0;
    void ajouterAnimal();


signals:
    void besoinRafraichir();
    void addToConsole(QColor couleur, QString source, QString message, bool newLine, bool important);



protected:
    bool charged;
    // ---------- Widgets ---------- //
    Personnage *personnage;
    bool gotPerso;

    QVector<Personnage*> vecteurPersos;
    Vue *vue;
    QVector<Affichable *> *vecteurAffichables;

    Map *map;
    Collision *collision;
    EffetsCollision *effets;

    Gerant *gerant;
};

#endif // CONTROLEUR_H
