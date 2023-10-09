#ifndef PERSONNAGE_H
#define PERSONNAGE_H


#include "Vivants/Vivant.h"
#include "Equipement/Equipement.h"
#include "Map/Map.h"
#include "Map/Collision.h"
#include "Vivants/Animal.h"


#include "Sorts/Sorts/Sort.h"
#include "Sorts/Sorts/ChangerArme.h"
#include "Sorts/Sorts/S_Fleche.h"
#include "Sorts/Sorts/S_DegatsArme.h"


#include "Sorts/Sorts/S_Assassinat.h"
#include "Sorts/Sorts/S_Invisibilite.h"
#include "Sorts/Sorts/S_WindWalk.h"
#include "Sorts/Sorts/S_Piege.h"
#include "Sorts/Sorts/S_ApotreMort.h"

#include "Sorts/Sorts/S_ExplosionTerre.h"
#include "Sorts/Sorts/S_ExplosionFeu.h"
#include "Sorts/Sorts/S_ExplosionGlace.h"
#include "Sorts/Sorts/S_ExplosionAir.h"
#include "Sorts/Sorts/S_DiffusionMulti.h"
#include "Sorts/Sorts/S_LaserEau.h"

#include "Sorts/Sorts/S_Vampirisme.h"
#include "Sorts/Sorts/S_Teleportation.h"
#include "Sorts/Sorts/S_DarkField.h"
#include "Sorts/Sorts/S_DarkCage.h"
#include "Sorts/Sorts/S_BlackHoleDark.h"

#include "Sorts/Sorts/S_DiffusionLumiere.h"
#include "Sorts/Sorts/S_LumiereBrulante.h"
#include "Sorts/Sorts/S_Heal.h"
#include "Sorts/Sorts/S_LumiereDivine.h"
#include "Sorts/Sorts/S_Light.h"


class Personnage : public Vivant
{
    Q_OBJECT

public:
    Personnage(bool persoPrincipalRecu, int typeRecu, QString nomRecu, Map *mapRecu, Collision *collisionRecu);
    ~Personnage();

    void findSave(int numero);


    void buildSprites();
    QImage* getSprite();
    double getPosXAffichage();
    double getPosYAffichage();
    QRectF getHitbox();

    Equipement* getEquipement() { return equipement; }

    QVector<Sort*>* getVecteurSorts();
    QVector<int> getStats() { return stats; }

    QString getNom();
    Arme *getArme() { return arme; }
    int getType() { return type; }
    QString getClasse() { return classe; }

    bool isInvisible() { return invisible; }
    bool isStun() { return stun; }
    int getMort() { return mort; }

    bool isPersoPrincipal() { return persoPrincipal; }
    QVector<QString> getDescriptionSorts() { return descriptionSorts; }

public slots:
    void changerArme();
    void actualiser();
    void deplacement(int,int);
    void attaquer(int seedRecu);
    void castSort(int seedRecu, int,double,double);
    void actualiserSorts();
    void ajoutAffichable(Affichable*);
    void setPos(double x, double y, int dir);

    void regenVie();
    void regenMana();

    void subirDegats(QVector<int> vecteurDegats);
    void setInvisible(bool invisibleRecu);
    void finStun();
    int getTempsStun();
    void setStun(bool);

    void ajouterVie(int);
    void setVie(int,bool);

    void revivre();
    void newPet(int);

    void envoyerMessage(QString);

signals:
    void changementMap(int,int);
    void ajouterAffichable(Affichable*);

    void envoyer(QString);
    void ajouterAnnonce(QString);
    void supprimerPerso(QString);
    void animalPosition(double,double,int);


    void signalSetPos(QString,double,double,int);
    void signalSetVie(QString,int,bool);



protected:
    bool gotAnimal;
    QVector<QVector<double>> chemin;
    Animal *animal;


    QVector<QString>  descriptionSorts;

    QMediaPlayer *player;
    bool persoPrincipal;

    QVector<QImage> imageMort;
    int mort;
    QTimer *timerMort;
    bool estMort;

    S_Fleche *sortFleche;
    S_DegatsArme *sortDegatsArme;

    int type;
    QString classe;
    bool invisible;
    bool stun;
    QTimer *timerStun;

    QTimer *timerVie;
    QTimer *timerMana;

    int seed;
    QString nom;
    int numeroSprite;

    // Equipement - Inventaire
    Equipement *equipement;
    Arme *arme;

    // Graphisme
    QImage sprites[14][3][4][13]; // Sprites
    int dureeActualisation;

    // Collision
    Collision *collision;

    Map *map;
    double etapeDeplacement;

    // Sorts
    QVector<Sort*> *sorts;
    QTimer *timerSorts;
    int sortEnTrainDeCast;
    bool isOnCast;
};

#endif // PERSONNAGE_H
