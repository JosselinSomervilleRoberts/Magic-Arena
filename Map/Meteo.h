#ifndef METEO_H
#define METEO_H

#include "Affichable.h"
#include <QPainter>
#include <QtWidgets>

class Meteo : public Affichable
{
    Q_OBJECT

public:
    Meteo();
    QImage getSprite();
    void buildSprites();

public slots:
    void rafraichir();

protected:
    QImage sprites[30];
    int actualSprite;

};

#endif // METEO_H
