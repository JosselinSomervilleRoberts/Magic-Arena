#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Map/Collision.h"

class Projectile : public Affichable
{
    Q_OBJECT

public:
    Projectile(QImage *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double porteeRecu, double posXRecu, double posYRecu, double vitesseXRecu, double vitesseYRecu, double accelXRecu, double accelYRecu);
    ~Projectile();

    void start(int seedRecu);
    void buildSprites() {}

    QImage* getSprite();
    double getPosXAffichage();
    double getPosYAffichage();
    QRectF getHitbox();
    QVector<int> getDegats() { return degatsFinaux; }
    void calculDegats();

    QString getLanceur() { return lanceur; }
    void rotateSprite();

public slots:
    void rafraichir();
    void collisionDetectee();

signals:
    void colliAffichables();
    void colliTerrain();

protected:
    QImage spriteActuel;
    bool doitEtreRafraichi;
    QString lanceur;
    int delai;

    Collision *collision;
    int duree;
    double portee;
    QImage *sprites;
    double deplacement;

    double vitesseX, vitesseY, accelX, accelY;
    bool passeAffichables;
    bool passeTerrain;
    bool fini;

    QVector<int> *statsPerso;

    QVector<int> degats;
    QVector<int> degatsFinaux;
    int tauxCrit, degatsCrit, tauxStun;
};

#endif // PROJECTILE_H
