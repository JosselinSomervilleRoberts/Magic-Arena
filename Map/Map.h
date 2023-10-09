#ifndef MAP_H
#define MAP_H

#include <QVector>
#include <QDebug>
#include <QtMath>
#include <QtSql>
#include <QtWidgets>
#include <QMediaPlayer>
#include <QMediaPlaylist>


class Map : public QObject
{
    Q_OBJECT

public:
    Map();
    ~Map();

    void setMap(int numeroRecu);

    int getNumero()  { return numero; }
    int getLargeur() { return largeur; }
    int getHauteur() { return hauteur; }

    QVector<QRectF>* getObstacles() { return &obstacles; }

public slots:
    void ajouterObstacles(QVector<QRectF>);
    void retirerObstacles(QVector<QRectF>);

    void setVolume(int);


private:
    QMediaPlayer *player;
    QMediaPlaylist *playlist;

    QVector<QVector<int>> map;
    int numero, largeur, hauteur;

    QVector<QRectF> obstacles;

    QSqlDatabase db; // Base de donnée contenant les tableaux d'accès
};

#endif // MAP_H
