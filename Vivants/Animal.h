#ifndef ANIMAL_H
#define ANIMAL_H

#include "Affichable.h"
#include "Map/Collision.h"

class Animal : public Affichable
{
    Q_OBJECT

public:
    Animal(QString maitreRecu, Collision *collisionRecu, int typeRecu, int posXRecu, int posYRecu);

    void buildSprites();
    QImage* getSprite();
    double getPosXAffichage();
    double getPosYAffichage();
    QRectF getHitbox();
    QString getMaitre();
    bool isInvisible() { return invisible; }


public slots:
    void setPosition(double posXRecu, double posYRecu, int orientationRecu);
    void setInvisible(bool);




protected:
    QString maitre;
    bool invisible;

    Collision *collision;
    int type, couleur, orientation;
    double etape;
    QVector<QVector<QImage>> sprites;
};

#endif // ANIMAL_H
