#include "Communication.h"

Communication::Communication(QApplication *app) : participant(0)
{
    gameIsOn = false;
    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        QNetworkSession *networkSession = new QNetworkSession(config, app);
        networkSession->open();
        networkSession->waitForOpened();

        if (networkSession->isOpen()) {
            // Save the used configuration
            QNetworkConfiguration config = networkSession->configuration();
            QString id;
            if (config.type() == QNetworkConfiguration::UserChoice) {
                id = networkSession->sessionProperty(
                        QLatin1String("UserChoiceConfiguration")).toString();
            } else {
                id = config.identifier();
            }

            QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
            settings.beginGroup(QLatin1String("QtNetwork"));
            settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
            settings.endGroup();
        }
    }


    connect(&client, SIGNAL(newMessage(QString,QString)),
            this, SLOT(recevoirMessage(QString,QString)));
    connect(&client, SIGNAL(newParticipant(QString)),
            this, SLOT(newParticipant(QString)));
    connect(&client, SIGNAL(participantLeft(QString)),
            this, SLOT(participantLeft(QString)));

    myNickName = client.nickName().left(client.nickName().indexOf("@"));//.replace("lilou", "Lilou la plus belle ♥");
    mapChosen = false;
}

void Communication::envoyer(QString message)
{
    client.sendMessage(message);
}

void Communication::recevoirMessage(const QString &from, const QString &messageRecu)
{
    if(messageRecu != last)
    {
        qDebug() << from << " said: " << messageRecu;
        emit addToConsole(Qt::red, "Communication", messageRecu, true, false);

        if (from.isEmpty() || messageRecu.isEmpty())
            return;


        QString message = messageRecu;
        QString nickName = from.left(from.indexOf("@"));//.replace("lilou", "Lilou la plus belle ♥");
        last = message;
        if(participant.contains(Participant{from, nickName}))
        {
            if(gameIsOn)
            {
                if(message.contains("fenetre_pret("))
                {
                    message.remove("fenetre_pret(");
                    QString nom = message.left(message.indexOf(")"));

                    for(int i=0; i<participant.length(); i++)
                    {
                        if(participant[i].nickName == nom)
                            participant[i].pret = true;
                    }

                    bool allPret = true;
                    for(int i=0; i<participant.length(); i++)
                    {
                        if(!participant[i].pret)
                            allPret = false;
                    }

                    if(allPret)
                        emit showVue();
                }
                if(message.contains("p("))
                {
                    message.remove("p(");
                    QString nom = message.left(message.indexOf(","));
                    message.remove(0, message.indexOf(",") + 1);
                    double x = message.left(message.indexOf(",")).toDouble();
                    message.remove(0, message.indexOf(",") + 1);
                    double y = message.left(message.indexOf(",")).toDouble();
                    message.remove(0, message.indexOf(",") + 1);
                    int orientation = message.left(message.indexOf(")")).toInt();
                    emit c_setPos(nom, x, y, orientation);
                }
                else if(message.contains("v("))
                {
                    message.remove("v(");
                    QString nom = message.left(message.indexOf(","));
                    message.remove(0, message.indexOf(",") + 1);
                    int vie = message.left(message.indexOf(",")).toInt();
                    message.remove(0, message.indexOf(",") + 1);
                    int stun = message.left(message.indexOf(")")).toInt();

                    if(stun == 1)
                        emit c_setVie(nom, vie, true);
                    else
                        emit c_setVie(nom, vie, false);
                }
                else if(message.contains("s("))
                {
                    message.remove("s(");
                    int seed = message.left(message.indexOf(",")).toInt();
                    message.remove(0, message.indexOf(",") + 1);
                    QString nom = message.left(message.indexOf(","));
                    message.remove(0, message.indexOf(",") + 1);
                    int sort = message.left(message.indexOf(",")).toInt();
                    message.remove(0, message.indexOf(",") + 1);
                    double x = message.left(message.indexOf(",")).toDouble();
                    message.remove(0, message.indexOf(",") + 1);
                    double y = message.left(message.indexOf(")")).toDouble();
                    emit c_sort(seed, nom, sort, x, y);
                }
                else if(message.contains("a("))
                {
                    message.remove("a(");
                    int seed = message.left(message.indexOf(",")).toInt();
                    message.remove(0, message.indexOf(",") + 1);
                    QString nom = message.left(message.indexOf(")"));
                    emit c_attaquer(seed, nom);
                }
            }
            else
            {
                if(message.contains("setMap("))
                {
                    message.remove("setMap(");
                    map = message.left(message.indexOf(")")).toInt();
                    mapChosen = true;

                    int nbPret = 0;
                    for(int i=0; i<participant.length(); i++)
                    {
                        if(participant[i].pret)
                            nbPret++;
                    }

                    if((nbPret == participant.length()) && (mapChosen))
                    {
                        gameIsOn = true;
                        emit start(map);
                    }
                }
                else if(message.contains("c_pret("))
                {
                    message.remove("c_pret(");
                    int seed = message.left(message.indexOf(",")).toInt();
                    message.remove(0, message.indexOf(",") + 1);
                    QString nom = message.left(message.indexOf(","));
                    message.remove(0, message.indexOf(",") + 1);
                    int classe = message.left(message.indexOf(",")).toInt();
                    message.remove(0, message.indexOf(",") + 1);
                    int animal = message.left(message.indexOf(",")).toInt();
                    message.remove(0, message.indexOf(",") + 1);
                    int booleen = message.left(message.indexOf(")")).toInt();

                    if(booleen == 1)
                    {
                        for(int i=0; i<participant.length(); i++)
                        {
                            if(participant[i].nickName == nom)
                            {
                                participant[i].pret = true;
                                participant[i].classe = classe;
                                participant[i].animal = animal;
                            }
                        }
                    }
                    else
                    {
                        for(int i=0; i<participant.length(); i++)
                        {
                            if(participant[i].name == nom)
                                participant[i].pret = false;
                        }
                    }

                    if((participant.length() == 1) && (participant[0].nickName == "lilou"))
                    {
                        gameIsOn = true;
                        mapChosen = true;
                        map = 10;
                        emit start(map);
                    }
                    else
                    {
                        int nbPret = 0;
                        bool monPersoPret = false;
                        for(int i=0; i<participant.length(); i++)
                        {
                            if(participant[i].pret)
                            {
                                nbPret++;
                                if(participant[i].nickName == myNickName)
                                    monPersoPret = true;
                            }
                        }

                        if((monPersoPret) && (nbPret == 1) && (!mapChosen))
                            emit chooseMap();

                        if((nbPret == participant.length()) && (mapChosen))
                        {
                            gameIsOn = true;
                            emit start(map);
                        }
                    }
                }
            }
        }
    }
}

Communication::~Communication()
{
    int length = participant.length();

    for(int i=0; i<length; i++)
        delete participant[i].timer;
}

QVector<Participant> Communication::getParticipants()
{
    for(int i=0; i<participant.length(); i++)
        participant[i].pret = false;

    return participant;
}


void Communication::newParticipant(const QString &name)
{
    emit addToConsole(Qt::red, "Communication", name + " joined", true, true);
    if (name.isEmpty())
        return;

    bool isIn = false;
    QString nickName = name.left(name.indexOf("@"));//.replace("lilou", "Lilou la plus belle ♥");

    for(int i=0; i<participant.length(); i++)
    {
        if(participant[i].nickName == nickName)
            isIn = true;
    }

    if(!gameIsOn)
    {
        if((participant.length() == 0) || (!isIn))
        {
            QString verif = name;
            verif.remove(0, name.indexOf("@") + 1);
            if(!verif.contains(nickName))
            {

                if(nickName == myNickName)
                {
                    participant.push_back(Participant{name, nickName, false,1,1,true,true});
                    emit connecte(true);
                    emit newPerso(nickName, true);
                }
                else
                {
                    participant.push_back(Participant{name, nickName, false,1,1,false,true});
                    emit newPerso(nickName, false);
                }
                participant.last().timer = new QTimer(this);
                participant.last().timer->setSingleShot(true);
                QObject::connect(participant.last().timer, SIGNAL(timeout()), this, SLOT(deleteParticipant()));
            }
        }
    }
    else
    {
        if(isIn)
        {
            for(int i=0; i<participant.length(); i++)
            {
                if(participant[i].nickName == nickName)
                {
                    participant[i].name = name;
                    participant[isIn].connected = true;
                    participant[isIn].timer->stop();
                }
            }
        }
    }
}

void Communication::participantLeft(const QString &name)
{
    emit addToConsole(Qt::red, "Communication", name + " left", true, true);
    if (name.isEmpty())
        return;

    int isIn = -1;
    QString nickName = name.left(name.indexOf("@"));//.replace("lilou", "Lilou la plus belle ♥");

    for(int i=0; i<participant.length(); i++)
    {
        if(participant[i].nickName == nickName)
            isIn = i;
    }

    if(isIn != -1)
    {
        if(!gameIsOn)
        {
            emit deletePerso(nickName);
            participant.removeAt(isIn);
        }
        else
        {
            participant[isIn].connected = false;
            participant[isIn].timer->start(3000);
        }
    }
}

void Communication::setMap(int mapRecu)
{
    envoyer("setMap(" + QString::number(mapRecu) + ")");
}

void Communication::deleteParticipant()
{
    for(int i=0; i<participant.length(); i++)
    {
        if((!(participant[i].connected)) && (!(participant[i].timer->isActive())))
        {
            QString nickName = participant[i].nickName;
            emit ajouterAnnonce(nickName + " a quitté la partie");
            delete participant[i].timer;
            participant.removeAt(i);
            emit deletePerso(nickName);
        }
    }
}
