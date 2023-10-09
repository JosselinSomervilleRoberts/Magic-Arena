#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QtWidgets>
#include <QMediaPlayer>

#include "Vivants/Vivant.h"
#include "Vivants/Personnage.h"
#include "Vivants/Animal.h"
#include "Vue.h"
#include "Affichable.h"

#include "Map/Map.h"
#include "Map/Collision.h"
#include "Map/EffetsCollision.h"

#include "Sorts/Boules/B_Teleportation.h"
#include "Communication/Communication.h"


#include "Vivants/Monstre.h"
#include "Gestion/GerantMulti.h"
#include "Gestion/GerantSolo.h"


class MaFenetre : public QWidget
{
    Q_OBJECT

public:
    MaFenetre();
    ~MaFenetre();

    void chargerJeu(int indexMapRecu, Communication *com);


public slots:
    void supprimerAffichable(Affichable *);
    void ajouterAffichable(Affichable *);

    void c_sort(int,QString, int, double, double);
    void c_attaquer(int,QString);
    void c_setPos(QString, double, double, int);
    void c_setVie(QString,int,bool);
    void nouveauPerso(QString, int, int, bool);
    void supprimerPerso(QString);

    void envoyer(QString);
    void lancerPartie();

    void ajouterAnimal();


signals:
    void besoinRafraichir();
    // Debug
    void addToConsole(QColor couleur, QString source, QString message, bool newLine, bool important);



private:
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
    Communication *communication;

    Gerant *gerant;
};


#endif // MAFENETRE_H
