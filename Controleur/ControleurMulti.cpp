#include "ControleurMulti.h"

ControleurMulti::ControleurMulti() : Controleur()
{}

ControleurMulti::~ControleurMulti()
{
    if(charged)
        delete communication;
}

void ControleurMulti::chargerJeu(int indexMapRecu, Communication *com)
{
    qsrand(QDateTime::currentDateTime ().toTime_t ());
    gotPerso = false;
    communication = com;

    vecteurAffichables = new QVector<Affichable *>();
    map = new Map();
    map->setMap(indexMapRecu);

    collision = new Collision(vecteurAffichables, map);
    effets = new EffetsCollision();
    QObject::connect(collision, SIGNAL(collisionDeAffichables(Affichable*,Affichable*)), effets, SLOT(checkEffetsCollision(Affichable *, Affichable *)));

    vue = new Vue(vecteurAffichables);
    vue->setMap(map);
    //QObject::connect(vue, SIGNAL(envoyer(QString)), this, SLOT(envoyer(QString)));
    QObject::connect(this, SIGNAL(besoinRafraichir()), vue, SLOT(rafraichir()));
    QObject::connect(this, SIGNAL(addToConsole(QColor,QString,QString,bool,bool)), vue, SLOT(addToConsole(QColor,QString,QString,bool,bool)));
    QObject::connect(collision, SIGNAL(addToConsole(QColor,QString,QString,bool,bool)), vue, SLOT(addToConsole(QColor,QString,QString,bool,bool)));

    //gerant = new GerantMulti(communication);
    gerant = new GerantSolo();
    QObject::connect(gerant, SIGNAL(signalCastSort(int,QString,int,double,double)), this, SLOT(c_sort(int,QString,int,double,double)));
    QObject::connect(gerant, SIGNAL(signalSetPos(QString,double,double, int)), this, SLOT(c_setPos(QString,double,double,int)));
    QObject::connect(gerant, SIGNAL(signalSetVie(QString, int, bool)), this, SLOT(c_setVie(QString,int,bool)));
    QObject::connect(gerant, SIGNAL(signalAttaquer(int,QString)), this, SLOT(c_attaquer(int,QString)));

    QObject::connect(vue, SIGNAL(signalAttaquer(QString)), gerant, SLOT(attaquer(QString)));
    QObject::connect(vue, SIGNAL(signalCastSort(QString,int,double,double)), gerant, SLOT(castSort(QString,int,double,double)));

    /*QObject::connect(communication, SIGNAL(c_sort(int,QString,int,double,double)), this, SLOT(c_sort(int,QString,int,double,double)));
    QObject::connect(communication, SIGNAL(c_setPos(QString,double,double, int)), this, SLOT(c_setPos(QString,double,double,int)));
    QObject::connect(communication, SIGNAL(c_setVie(QString, int, bool)), this, SLOT(c_setVie(QString,int,bool)));
    QObject::connect(communication, SIGNAL(c_attaquer(int,QString)), this, SLOT(c_attaquer(int,QString)));*/
    QObject::connect(communication, SIGNAL(deletePerso(QString)), this, SLOT(supprimerPerso(QString)));
    QObject::connect(communication, SIGNAL(showVue()), this, SLOT(lancerPartie()));
    QObject::connect(communication, SIGNAL(ajouterAnnonce(QString)), vue, SLOT(ajouterAnnonce(QString)));
    QObject::connect(communication, SIGNAL(addToConsole(QColor,QString,QString,bool,bool)), vue, SLOT(addToConsole(QColor,QString,QString,bool,bool)));

    QVector<Participant> participants = communication->getParticipants();
    for(int i=0; i<participants.length(); i++)
        nouveauPerso(participants[i].nickName, participants[i].classe, participants[i].animal, participants[i].joueur);


    communication->envoyer("fenetre_pret(" + personnage->getNom() + ")");
    vue->showFullScreen();
    charged = true;
}


void ControleurMulti::lancerPartie()
{
    communication->envoyer("p(" + personnage->getNom() + "," + QString::number(personnage->getPosX()) + "," + QString::number(personnage->getPosY()) + "," + QString::number(personnage->getOrientation()) + ")");
    vue->start();
    vue->rafraichirInterface();
}
