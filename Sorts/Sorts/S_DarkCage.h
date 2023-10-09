#ifndef S_DARKCAGE_H
#define S_DARKCAGE_H

#include "Sorts/Sorts/Sort.h"
#include "Sorts/Shields/Sh_DarkCage.h"


class S_DarkCage : public Sort
{
    Q_OBJECT

public:
    S_DarkCage(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu);
    ~S_DarkCage();

    void action();
    void actionDebut();
    void actionFin();
    void buildSprites();

signals:
    void add(QVector<QRectF> vecteur);
    void remove(QVector<QRectF> vecteur);

public slots:
    void next();

protected:
    QVector<QRectF> vecteur;
    QTimer *timer;
    bool isOn;
};

#endif // S_DARKCAGE_H
