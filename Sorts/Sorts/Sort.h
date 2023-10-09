#ifndef SORT_H
#define SORT_H

#include <QtWidgets>
#include "Affichable.h"
#include "Map/Collision.h"

class Sort : public QObject
{
    Q_OBJECT


public:
    Sort(QString lanceurRecu, QVector<int> *statsRecu, Collision *collisionRecu);
    ~Sort();

    bool isOnCd() { return isOnCooldown; }
    bool isCasting() { return isOnCast; }
    bool isAvailable();
    bool isInRange(int distance);
    bool isCiblable();

    int getPortee() { return porteeBase; }
    int getIcone() { return icone; }
    double getCooldownRemaining();
    double getCooldown();
    int getCast() { return dureeCast; }
    int getCoutMana() { return coutMana; }

    virtual void actionDebut() = 0;
    virtual void action() = 0;
    virtual void actionFin() = 0;
    virtual void buildSprites() = 0;

    QVector<int> calculDegats();





public slots:
    void cast(int seedRecu, double x, double y);
    void finCast();
    void finAction();
    void finCooldown();
    void end();


signals:
    void ajouterAffichable(Affichable*);
    // Debug
    void addToConsole(QColor couleur, QString source, QString message, bool newLine, bool important);


protected:
    QMediaPlayer *player;

    QVector<QVector<QImage>> sprites;
    int seed;
    QString lanceur;
    int coutMana;

    Collision *collision;
    int porteeBase;
    bool ciblable;

    int dureeCast;
    bool isOnCast;

    int dureeAction;
    bool isOnAction;
    QTimer *timerAction;

    int dureeCooldown;
    bool isOnCooldown;
    QTimer *timerCooldown;

    int icone;

    double posX, posY;
    QVector<int> *stats;
};

#endif // SORT_H
