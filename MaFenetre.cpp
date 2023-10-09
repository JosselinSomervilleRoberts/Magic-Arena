#include "MaFenetre.h"


/* Constructeur
 * Ne reçoit pas d'arguments */

MaFenetre::MaFenetre() : QWidget()
{
    charged = false;
}

MaFenetre::~MaFenetre()
{
    if(charged)
    {
        delete map;
        delete collision;
        delete effets;

        delete vue;

        int size = vecteurAffichables->length();
        for(int i=0; i<size; i++)
            delete vecteurAffichables->takeAt(0);

        delete vecteurAffichables;
        delete gerant;
    }
}




/* Fonction qui permet d'initialiser le programme
 * Ne reçoit pas d'arguments */

void MaFenetre::chargerJeu(int indexMapRecu, Communication *com)
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


    envoyer("fenetre_pret(" + personnage->getNom() + ")");
    vue->showFullScreen();
    charged = true;
}

void MaFenetre::envoyer(QString message)
{
    for(int i=0; i<1; i++)
        communication->envoyer(message);
}

void MaFenetre::supprimerPerso(QString nom)
{
    emit addToConsole(Qt::white, "MaFenetre", "SUPPRIMER PERSO = " + nom, false, true);
    for(int i=0; i<vecteurPersos.length(); i++)
    {
        if(vecteurPersos[i]->getNom() == nom)
        {
            emit addToConsole(Qt::white, "", "   / found", false, true);
            if(nom == personnage->getNom())
            {
                emit addToConsole(Qt::white, "", "   / mainPerso", true, true);
                gotPerso = false;
                addToConsole(Qt::white, "MaFenetre", "Defaite", true, true);
                delete communication;
                vue->defaite();
            }

            emit addToConsole(Qt::white, "", "mainPerso", true, true);
            supprimerAffichable(vecteurPersos.takeAt(i));
            vue->ajouterAnnonce(nom + " a perdu !");
        }
    }

    emit addToConsole(Qt::white, "MaFenetre", "longueur vecteurPerso = " + QString::number(vecteurPersos.length()), false, true);
    emit addToConsole(Qt::white, "", "   / gotPerso = " + QString::number(gotPerso), true, true);

    if((vecteurPersos.length() == 1) && (gotPerso))
    {
        qDebug() << "victoire";
        emit addToConsole(Qt::white, "", "   / mainPerso", true, true);
        gotPerso = false;
        addToConsole(Qt::white, "MaFenetre", "Victoire", true, true);
        delete communication;
        vue->victoire();

        emit addToConsole(Qt::white, "", "mainPerso", true, true);
        supprimerAffichable(vecteurPersos.takeFirst());
        //vue->ajouterAnnonce( + " a gagné !");

        //if(communication->getParticipants().length() > 1) // Si il y a au moins un joueur
            ajouterAnimal();
            qDebug() << "finVictoire";
    }
}

void MaFenetre::nouveauPerso(QString nom, int classe, int animal, bool persoPrincipal)
{
    Personnage *perso = new Personnage(persoPrincipal, classe, nom, map, collision);
    if(persoPrincipal) // Si c'est le perso du joueur
    {
        gotPerso = true;
        personnage = perso;
        vue->setPerso(perso);
        QObject::connect(perso, SIGNAL(actualiserInterface()), vue, SLOT(rafraichirInterface()));
        QObject::connect(perso, SIGNAL(signalSetPos(QString,double,double,int)), gerant, SLOT(setPos(QString,double,double,int)));
        QObject::connect(perso, SIGNAL(signalSetVie(QString,int,bool)), gerant, SLOT(setVie(QString,int,bool)));
        QObject::connect(vue, SIGNAL(signalDeplacer(int,int)), perso, SLOT(deplacement(int,int)));
    }

    vecteurPersos.push_back(perso);
    QObject::connect(perso, SIGNAL(ajouterAffichable(Affichable*)), this, SLOT(ajouterAffichable(Affichable*)));
    QObject::connect(perso, SIGNAL(finish(Affichable*)), this, SLOT(supprimerAffichable(Affichable*)));
    QObject::connect(perso, SIGNAL(ajouterAnnonce(QString)), vue, SLOT(ajouterAnnonce(QString)));
    perso->newPet(animal);
    ajouterAffichable(perso);
    QObject::connect(perso, SIGNAL(supprimerPerso(QString)), this, SLOT(supprimerPerso(QString)));
}

void MaFenetre::c_attaquer(int seed, QString nom)
{
    emit addToConsole(Qt::white, "MaFenetre", nom + " attaquer", true, false);

    for(int i=0; i<vecteurPersos.length(); i++)
    {
        if(vecteurPersos[i]->getNom() == nom)
            vecteurPersos[i]->attaquer(seed);
    }
}

void MaFenetre::c_setVie(QString nom, int vieRecu, bool stunRecu)
{
    emit addToConsole(Qt::white, "MaFenetre", "set " + nom + " vie = " + QString::number(vieRecu) + "   / stun = " + QString::number(stunRecu), true, false);
    for(int i=0; i<vecteurPersos.length(); i++)
    {
        if(vecteurPersos[i]->getNom() == nom)
            vecteurPersos[i]->setVie(vieRecu, stunRecu);
    }
}

void MaFenetre::c_setPos(QString nom, double x, double y, int orientation)
{
    emit addToConsole(Qt::white, "MaFenetre", "set " + nom + " posX = "+ QString::number(x) + "   / posY = " + QString::number(y) + "   / orientation = " + QString::number(orientation), true, false);

    for(int i=0; i<vecteurPersos.length(); i++)
    {
        if(vecteurPersos[i]->getNom() == nom)
            vecteurPersos[i]->setPos(x, y, orientation);
    }
    emit besoinRafraichir();
}

void MaFenetre::c_sort(int seed, QString nom, int sort, double x, double y)
{
    emit addToConsole(Qt::white, "MaFenetre", nom + " cast sort = " + QString::number(sort) + " at posX = "+ QString::number(x) + "   / posY = " + QString::number(y), true, false);

    for(int i=0; i<vecteurPersos.length(); i++)
    {
        if(vecteurPersos[i]->getNom() == nom)
            vecteurPersos[i]->castSort(seed, sort, x, y);
    }
}


void MaFenetre::lancerPartie()
{
    envoyer("p(" + personnage->getNom() + "," + QString::number(personnage->getPosX()) + "," + QString::number(personnage->getPosY()) + "," + QString::number(personnage->getOrientation()) + ")");
    vue->start();
    vue->rafraichirInterface();
}


void MaFenetre::supprimerAffichable(Affichable * affichable)
{
    if((affichable != nullptr) && (*affichable == 1))
    {
        vecteurAffichables->removeOne(affichable);
        delete affichable;
        emit addToConsole(Qt::white, "MaFenetre", "affichable deleted   / vecteurAffichables length = " + QString::number(vecteurAffichables->length()), true, true);
        emit besoinRafraichir();
    }
    else
    {
        emit addToConsole(Qt::white, "MaFenetre", "affichable alredy deleted", true, true);
        vecteurAffichables->removeOne(affichable);
        emit addToConsole(Qt::white, "MaFenetre", "affichable remove from vecteur", true, true);
    }

    /*for(int i=0; i<vecteurAffichables->length(); i++)
    {
        if(!((affichable != nullptr) && (*affichable == 1)))
        {
            emit addToConsole(Qt::red, "MaFenetre", "affichable alredy deleted", true, true);
            vecteurAffichables->removeOne(affichable);
            emit addToConsole(Qt::red, "MaFenetre", "affichable remove from vecteur", true, true);
        }
    }*/
}

void MaFenetre::ajouterAffichable(Affichable * affichable)
{
    vecteurAffichables->push_back(affichable);
    QObject::connect(affichable, SIGNAL(besoinRafraichir()), vue, SLOT(rafraichir()));
    QObject::connect(affichable, SIGNAL(finish(Affichable *)), this, SLOT(supprimerAffichable(Affichable *)));
    QObject::connect(affichable, SIGNAL(addToConsole(QColor,QString,QString,bool,bool)), vue, SLOT(addToConsole(QColor,QString,QString,bool,bool)));
}

void MaFenetre::ajouterAnimal()
{
    int id = 1 + qrand()%98;

    addToConsole(Qt::white, "MaFenetre", "ajouterAnimal = " + QString::number(id), true, true);


    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../data/databases/save");
    db.open();
    QSqlQuery query(db);
    if(!query.exec("UPDATE animaux SET obtenu=1 WHERE id=" + QString::number(id)))
        QMessageBox::critical(this, "Erreur", "Impossible de sauvegarder");

    db.close();
}
