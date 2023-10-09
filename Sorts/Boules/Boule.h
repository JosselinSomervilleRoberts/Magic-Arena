#ifndef BOULE_H
#define BOULE_H

#include "Map/Collision.h"
#include <QMediaPlayer>

class Boule : public Affichable
{
    Q_OBJECT

public:
    Boule(QVector<QImage> *spritesRecu, QString lanceurRecu, Collision *collisionRecu, QVector<int> *statsPersoRecu, double posXRecu, double posYRecu);
    ~Boule();

    void start(int seedRecu);
    void buildSprites() {}

    QImage* getSprite();
    double getPosXAffichage();
    double getPosYAffichage();
    QRectF getHitbox();
    QVector<int> getDegats() { return degatsFinaux; }
    void calculDegats();

    QString getLanceur() { return lanceur; }

public slots:
    void rafraichir();


protected:
    QString musique;
    QString lanceur;

    Collision *collision;
    int duree, etape, etapeMax;
    QVector<QImage> *sprites;

    QVector<int> *statsPerso;

    QVector<int> degats;
    QVector<int> degatsFinaux;
    int tauxCrit, degatsCrit, tauxStun;
};

#endif // BOULE_H
