#ifndef SERVEUR_H
#define SERVEUR_H

#include "Communication/Communication.h"

class Serveur : public Communication
{
    Q_OBJECT

public:
    Serveur(QApplication *appRecu);

public slots:
    void interpretationMessage(QString expediteur, QString message);
    void lancerPartie();

protected:
    int id;
    QVector<int> idClient;
    bool gameIsOn;
};

#endif // SERVEUR_H
