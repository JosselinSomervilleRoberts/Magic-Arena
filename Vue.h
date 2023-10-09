#ifndef VUE_H
#define VUE_H

#include <QtWidgets>

#include "Affichable.h"
#include "Vivants/Personnage.h"
#include "Vivants/Animal.h"
#include "Vivants/Vivant.h"
#include "Map/Map.h"
#include "Communication/Communication.h"
#include "Sorts/Sorts/ChangerArme.h"

#include "Console.h"
#include "Parametres.h"

class Vue : public QWidget
{
    Q_OBJECT

public:
    Vue(QVector<Affichable*> *vecteurAffichablesRecu);
    ~Vue();
    void start();

    void victoire();
    void defaite();

    void setMap(Map *mapRecu);
    void setPerso(Personnage *personnage);

public slots:
    void rafraichir();
    void rafraichirInterface();
    void addWidget(QWidget *widget, int x, int y, int w, int h);

    void ajouterAnnonce(QString);
    void rafraichirAnnonce();

    void addToConsole(QColor couleur, QString source, QString message, bool newLine, bool important);

    void toucheAppuyee(int key, double x, double y);


    void newRaccourcis(QVector<int>);
    void deleteParametres();
    void findParametres();


protected :
    void keyPressEvent (QKeyEvent *event); // Détecte l'appui d'une touche clavier
    void keyReleaseEvent (QKeyEvent *event); // Détecte l'appui d'une touche clavier
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

signals:
    void signalAttaquer(QString);
    void signalCastSort(QString, int, double, double);
    void signalDeplacer(int, int);
    void envoyer(QString);

    void deplacer(int, int);

protected:
    QVector<int> touches;
    QVector<int> raccourcis;

    Console * console;
    bool consoleIsOn;

    Parametres * parametres;
    bool parametresIsOn;

    QVector<QString>  descriptionSorts;

    bool fini;
    bool hasStarted;

    int fps;
    int sortShown;
    bool drawParametres;

    QVector<QString> vecteurAnnonces;
    QTimer *timerAnnonce;

    Map *map;
    double xMap, yMap;

    Personnage *perso;
    bool gotPerso;

    int width, height, tailleCase, dpi;

    QGridLayout *layoutPrincipal;


    QLabel *labelPrincipal;
    QPixmap pixmapPrincipal;

    QPixmap pixmapMap;

    QLabel *labelInterface;
    QPixmap pixmapInterface;


    bool afficherHitboxes;

    QVector<Affichable*> *vecteurAffichables;
    int deplacementX, deplacementY;

    QTimer *timerRefresh;
    QElapsedTimer lastRefresh;
};

#endif // VUE_H
