#include "Serveur.h"

Serveur::Serveur(QApplication *appRecu) : Communication(appRecu), idClient(0, 0)
{
    gameIsOn = false;
    id = 0;
    QObject::connect(this, SIGNAL(recevoir(QString,QString)), this, SLOT(interpretationMessage(QString,QString)));
}

void Serveur::interpretationMessage(QString expediteur, QString message)
{
    int exp = expediteur.toInt();
    if(exp == -1)
    {
        if(message == "sendID")
        {
            envoyer(QString::number(id) + "/" + "IDis" + QString::number(idClient.length()+1));
        }
        else if(message.contains("connectAs"))
        {
            int idClientProvisoire = QString::number(message.right(message.length()-9));
            if(!idClient.contains(idClientProvisoire))
            {
                idClient.push_back(idClientProvisoire);
                envoyer(QString::number(id) + "/" + "OK" + QString::number(idClientProvisoire));
            }
            else
            {
                envoyer(QString::number(id) + "/" + "REFUSE" + QString::number(idClientProvisoire));
            }
        }
    }
    else if((gameIsOn) && (idClient.contains(exp)))
    {
        if(message.contains("keyPressed"))
        {
            message.remove("keyPressed");
            int touche = message.left(message.indexOf(",")).toInt();
            message.remove(0,message.indexOf(",")+1);
            int mouseX = message.left(message.indexOf(",")).toInt();
            message.remove(0,message.indexOf(",")+1);
            int mouseY = message.toInt();
        }
    }
}

void Serveur::lancerPartie()
{
    gameIsOn = true;
}


