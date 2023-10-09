#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "chatdialog.h"
#include "client.h"

#include <QtCore/QSettings>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkSession>
#include <QApplication>
#include <QTimer>
#include <QColor>



struct Participant
{
    QString name;
    QString nickName;
    bool pret;
    int classe;
    int animal;
    bool joueur;
    bool connected;
    QTimer *timer;

    bool operator!=(const Participant& part) const
    {
        if(part.nickName == this->nickName)
            return false;

        return true;
    }

    bool operator==(const Participant& part) const
    {
        if(part.nickName == this->nickName)
            return true;

        return false;
    }
};


class Communication : public QObject
{
    Q_OBJECT

public:
    Communication(QApplication *app);
    ~Communication();

public slots:
    void envoyer(QString message);
    void recevoirMessage(const QString &from, const QString &message);
    QVector<Participant> getParticipants();
    void setMap(int);

private slots:
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);
    void deleteParticipant();

signals:
    void recevoir(QString);
    void newPerso(QString, bool);
    void deletePerso(QString);
    void ajouterAnnonce(QString);
    void connecte(bool);

    void c_sort(int, QString, int, double, double);
    void c_attaquer(int, QString);
    void c_setPos(QString, double, double, int);
    void c_setVie(QString, int, bool);

    void start(int);
    void showVue();
    void chooseMap();

    // Debug
    void addToConsole(QColor couleur, QString source, QString message, bool newLine, bool important);


protected:
    QString last;

    bool mapChosen;
    int map;
    bool gameIsOn;
    Client client;
    QString myNickName;

    QVector<Participant> participant;
};

#endif // COMMUNICATION_H
