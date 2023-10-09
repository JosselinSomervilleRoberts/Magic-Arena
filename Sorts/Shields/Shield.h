#ifndef SHIELD_H
#define SHIELD_H

#include "Map/Collision.h"

class Shield : public Affichable
{
    Q_OBJECT

public:
    Shield(QVector<QImage> *spritesRecu, QString lanceurRecu, QVector<int> *statsPersoRecu, double *posXRecu, double *posYRecu);
    ~Shield();

    void start(int seedRecu);
    void appliquerEffets();
    void annulerEffets();
    void buildSprites() {}

    QImage* getSprite();
    double getPosXAffichage();
    double getPosYAffichage();
    QRectF getHitbox();

    QString getLanceur() { return lanceur; }

public slots:
    void rafraichir();
    void end();

protected:
    double offsetX, offsetY;
    QString lanceur;
    double *posXPerso;
    double *posYPerso;

    int etapeShield;
    int dureeAvant, dureeShield, dureeApres;
    int etape, etapeMax;
    QVector<QImage> *sprites;

    QVector<int> *statsPerso;

    QVector<int> stats;
};

#endif // SHIELD_H
