#include "MonLauncher.h"

MonLauncher::MonLauncher(QApplication *app) : QWidget(), fenetre()
{
    idAnimal = 1;
    animalShown = false;
    this->setWindowIcon(QIcon("../data/images/icone.ico"));
    pret = false;
    qsrand(QDateTime::currentDateTime ().toTime_t ());

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../data/databases/personnages");
    com = new Communication(app);

    QRect rec = QApplication::desktop()->screenGeometry();
    height = rec.height();
    width = rec.width();
    tailleCase = qMin(width / 80, int(height / 42));
    dpi = QApplication::desktop()->physicalDpiX();

    setFixedSize(40*tailleCase, 21*tailleCase);
    setWindowFlags(Qt::FramelessWindowHint);

    texteConnexion = new QLabel(this);
    texteConnexion->setText("Connexion");
    texteConnexion->setStyleSheet("width: " + QString::number(40*tailleCase) + "px; height: " + QString::number(4.2*tailleCase) + "px; background-color: rgba(255,255,255,200); color: rgba(0,0,0,200); font-size: " + QString::number(1.5*tailleCase) + "px;");
    texteConnexion->setAlignment(Qt::AlignCenter);
    texteConnexion->lower();

    pixmapFond = QPixmap("../data/images/launcher/fond.png").scaled(40*tailleCase, 21*tailleCase);
    labelFond = new QLabel(this);
    labelFond->setPixmap(pixmapFond);
    labelFond->lower();

    gif = new QMovie("../data/images/launcher/connexion.gif");
    gif->setScaledSize(QSize(2*tailleCase, 2*tailleCase));
    gifConnexion = new QLabel(this);
    gifConnexion->setMovie(gif);
    gif->start();
    gifConnexion->raise();

    QPushButton *quitter = new QPushButton(this);
    quitter->setStyleSheet("width: " + QString::number(tailleCase) + "px; height: " + QString::number(tailleCase) + "px; border-image: url(../data/images/launcher/croix.png) 0 0 0 0 stretch stretch;");
    QObject::connect(quitter, SIGNAL(clicked()), this, SLOT(close())); // Connection du bouton à la fermeture de la fenêtre
    quitter->raise();

    QPushButton *reduction = new QPushButton(this);
    reduction->setStyleSheet("width: " + QString::number(tailleCase) + "px; height: " + QString::number(tailleCase) + "px; border-image: url(../data/images/launcher/reduire.png) 0 0 0 0 stretch stretch;");
    QObject::connect(reduction, SIGNAL(clicked()), this, SLOT(reduire())); // Connection du bouton à la fermeture de la fenêtre
    reduction->raise();



    layoutPrincipal = new QGridLayout(this);
    layoutPrincipal->setContentsMargins(0,0,0,0);
    layoutPrincipal->setSpacing(0);

    layoutPrincipal->addWidget(labelFond, 0,0,40,80);
    layoutPrincipal->addWidget(texteConnexion, 32,0,8,80);
    layoutPrincipal->addWidget(gifConnexion, 34,24,4,8);
    layoutPrincipal->addWidget(reduction, 0,76,2,2);
    layoutPrincipal->addWidget(quitter, 0,78,2,2);

    setLayout(layoutPrincipal);

    QObject::connect(com, SIGNAL(connecte(bool)), this, SLOT(launch(bool)));
    QObject::connect(com, SIGNAL(newPerso(QString, bool)), this, SLOT(newParticipant(QString, bool)));
    QObject::connect(com, SIGNAL(deletePerso(QString)), this, SLOT(deleteParticipant(QString)));
    QObject::connect(com, SIGNAL(start(int)), this, SLOT(start(int)));
    QObject::connect(com, SIGNAL(chooseMap()), this, SLOT(chooseMap()));

}

MonLauncher::~MonLauncher()
{
    delete gif;
}

void MonLauncher::launch(bool connecte)
{
    if(connecte)
    {
        layoutPerso = new QGridLayout(this);
        layoutPerso->setContentsMargins(0,0,0,0);
        layoutPerso->setSpacing(0);
        widgetPerso = new QWidget(this);
        widgetPerso->setLayout(layoutPerso);

        QLabel *label = new QLabel(this);
        QPixmap pixmap(28*tailleCase, 21* tailleCase);
        pixmap.fill(Qt::transparent);
        QPainter p(&pixmap);
        p.setOpacity(0.75);
        p.drawImage(0,0,QImage("../data/images/launcher/fondPerso.png").scaled(28*tailleCase,21*tailleCase));
        p.end();
        label->setPixmap(pixmap);
        layoutPerso->addWidget(label, 0, 0, 42, 56);

        QPainter painter(&pixmapFond);
        painter.setOpacity(0.75);
        painter.drawImage(0,0,QImage("../data/images/launcher/fond2.png").scaled(40*tailleCase,21*tailleCase));
        painter.end();
        labelFond->setPixmap(pixmapFond);

        layoutPrincipal->removeWidget(texteConnexion);
        delete texteConnexion;
        layoutPrincipal->removeWidget(gifConnexion);
        delete gifConnexion;

        boutonPret = new QPushButton("Prêt !", this);
        boutonPret->setStyleSheet("width: " + QString::number(6*tailleCase) + "px; height: " + QString::number(1*tailleCase) + "px; background-color: rgba(40,40,40,200); border: 1px solid rgba(255,255,255,200); border-radius: 2px; font-size: " + QString::number(0.5*tailleCase) + "px; color: rgba(255,255,255,200);");
        boutonPret->setCheckable(true);
        boutonPret->setChecked(true);
        QObject::connect(boutonPret, SIGNAL(pressed()), this, SLOT(setPret()));
        layoutPrincipal->addWidget(boutonPret, 37, 63, 2, 12);

        boutonSwitch = new QPushButton("Choisir un animal", this);
        boutonSwitch->setStyleSheet("width: " + QString::number(6*tailleCase) + "px; height: " + QString::number(1*tailleCase) + "px; background-color: rgba(40,40,40,200); border: 1px solid rgba(255,255,255,200); border-radius: 2px; font-size: " + QString::number(0.5*tailleCase) + "px; color: rgba(255,255,255,200);");
        boutonSwitch->setCheckable(true);
        boutonSwitch->setChecked(true);
        QObject::connect(boutonSwitch, SIGNAL(pressed()), this, SLOT(switchFenetres()));
        layoutPrincipal->addWidget(boutonSwitch, 34, 63, 3, 12);

        group = new QButtonGroup(this);
        group->setExclusive(true);

        labelsPerso = QVector<QLabel*>(0);
        for(int i=0; i<22; i++)
        {
            QLabel *label = new QLabel(this);
            labelsPerso.push_back(label);
        }
        layoutPrincipal->addWidget(labelsPerso[20], 35, 59, 3, 3);
        layoutPrincipal->addWidget(labelsPerso[21], 35, 76, 3, 3);
        labelsPerso[20]->setStyleSheet("width: " + QString::number(1.5*tailleCase) + "px; height: " + QString::number(1.5*tailleCase) + "px; border: 1px solid rgb(80,80,80); border-radius: 3px;");
        labelsPerso[21]->setStyleSheet("width: " + QString::number(1.5*tailleCase) + "px; height: " + QString::number(1.5*tailleCase) + "px; border: 1px solid rgb(80,80,80); border-radius: 3px;");
        labelsPerso[21]->setPixmap(QPixmap("../data/images/launcher/animaux/1.png").scaled(1.5*tailleCase,1.5*tailleCase));


        for(int i=1; i<=4; i++)
        {
            QPushButton *bouton = new QPushButton(this);
            bouton->setStyleSheet("width: " + QString::number(6*tailleCase) + "px; height: " + QString::number(6*tailleCase) + "px; border-image: url(../data/images/faces/" + QString::number(i) + ".png) 0 0 0 0 stretch stretch;");
            bouton->setCheckable(true);
            group->addButton(bouton, i);
            layoutPerso->addWidget(bouton, 2,-8+12*i,12,12);
        }
        QObject::connect(group, SIGNAL(buttonPressed(int)), this, SLOT(selectPerso(int)));



        group->button(1)->setChecked(true);
        labelsPerso[19]->setText("Aucun bonus apporté");
        selectPerso(1);

        layoutPerso->addWidget(labelsPerso[0], 16, 5, 5,5);
        layoutPerso->addWidget(labelsPerso[2], 16, 21, 5,5);
        layoutPerso->addWidget(labelsPerso[4], 16, 37, 5,5);

        layoutPerso->addWidget(labelsPerso[1], 16, 11, 5,8);
        layoutPerso->addWidget(labelsPerso[3], 16, 27, 5,8);
        layoutPerso->addWidget(labelsPerso[5], 16, 43, 5,8);

        layoutPrincipal->addWidget(widgetPerso, 0, 0, 42, 56);
    }
}

void MonLauncher::selectPerso(int index)
{
    if(!pret)
    {
        labelsPerso[20]->setPixmap(QPixmap("../data/images/faces/" + QString::number(index) + ".png").scaled(1.5*tailleCase,1.5*tailleCase));
        QSqlDatabase db;
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("../data/databases/personnages");
        db.open();
        QSqlQuery query(db);
        if(query.exec("SELECT * FROM persos WHERE id=" + QString::number(index)))
        {
            while(query.next())
            {
                QString nom = query.value(23).toString();
                labelsPerso[18]->setText(nom);
                labelsPerso[18]->setStyleSheet("color: rgba(255,201,14,200); font-size: " + QString::number(tailleCase) + "px; width: " + QString::number(10*tailleCase) + "px; height: " + QString::number(1*tailleCase) + "px;");
                labelsPerso[18]->setAlignment(Qt::AlignCenter);
                layoutPrincipal->addWidget(labelsPerso[18], 31, 59, 2, 20);

                labelsPerso[19]->setStyleSheet("color: rgba(255,201,14,200); font-size: " + QString::number(tailleCase/2) + "px; width: " + QString::number(10*tailleCase) + "px; height: " + QString::number(0.5*tailleCase) + "px;");
                labelsPerso[19]->setAlignment(Qt::AlignCenter);
                layoutPrincipal->addWidget(labelsPerso[19], 33, 59, 1, 20);

                for(int i=0; i<3; i++)
                {
                    QPixmap pixmap(2.5*tailleCase,2.5*tailleCase);
                    pixmap.fill(QColor(200,200,200));
                    QPainter painter(&pixmap);
                    painter.drawPixmap(0,0,QPixmap("../data/images/armes/" + QString::number(query.value(i+19).toInt()) + ".png").scaled(2.5*tailleCase,2.5*tailleCase));
                    painter.setBrush(Qt::transparent);
                    QPen pen(QColor(45,22,0));
                    pen.setWidth(3);
                    painter.setPen(pen);
                    painter.drawRect(QRect(0,0,2.5*tailleCase-1,2.5*tailleCase-1));
                    painter.end();
                    labelsPerso[2*i]->setPixmap(pixmap);

                    QSqlDatabase db2;
                    db2 = QSqlDatabase::addDatabase("QSQLITE");
                    db2.setDatabaseName("../data/databases/equipement");
                    db2.open();
                    QSqlQuery query2(db2);
                    if(query2.exec("SELECT * FROM arme WHERE id=" + QString::number(query.value(i+19).toInt())))
                    {
                        query2.next();

                        QPixmap pixmap(3.75*tailleCase,2.5*tailleCase);
                        pixmap.fill(Qt::transparent);
                        QPainter painter(&pixmap);
                        QPen pen(QColor(27,119,60));
                        painter.setFont(QFont("Times", (tailleCase/3)*142/dpi));
                        painter.setPen(pen);
                        painter.drawImage(0,2,QImage("../data/images/symboles/terre.png").scaled(tailleCase/2,tailleCase/2));
                        painter.drawText(QRect(tailleCase/1.6,0, 3*tailleCase, tailleCase/1.6), QString::number(query2.value(2).toInt()) + " - " + QString::number(query2.value(3).toInt()));

                        pen.setColor(QColor(232,65,35));
                        painter.setPen(pen);
                        painter.drawImage(0,2+tailleCase/1.6,QImage("../data/images/symboles/feu.png").scaled(tailleCase/2,tailleCase/2));
                        painter.drawText(QRect(tailleCase/1.6,tailleCase/1.6,3*tailleCase, tailleCase/1.6), QString::number(query2.value(4).toInt()) + " - " + QString::number(query2.value(5).toInt()));

                        pen.setColor(QColor(2,82,142));
                        painter.setPen(pen);
                        painter.drawImage(0,2+tailleCase/0.8,QImage("../data/images/symboles/eau.png").scaled(tailleCase/2,tailleCase/2));
                        painter.drawText(QRect(tailleCase/1.6,tailleCase/0.8, 3*tailleCase, tailleCase/1.6), QString::number(query2.value(6).toInt()) + " - " + QString::number(query2.value(7).toInt()));

                        pen.setColor(QColor(77,76,81));
                        painter.setPen(pen);
                        painter.drawImage(0,2+tailleCase*1.875,QImage("../data/images/symboles/air.png").scaled(tailleCase/2,tailleCase/2));
                        painter.drawText(QRect(tailleCase/1.6,tailleCase*1.875, 3*tailleCase, tailleCase/1.6), QString::number(query2.value(8).toInt()) + " - " + QString::number(query2.value(9).toInt()));
                        painter.end();
                        labelsPerso[1+2*i]->setPixmap(pixmap);
                    }
                    db2.close();
                }

                QPixmap pixmap3 = QPixmap(2.5*tailleCase,2.5*tailleCase);
                pixmap3.fill(Qt::transparent);
                QPainter painter3(&pixmap3);
                painter3.setOpacity(0.75);
                painter3.drawImage(tailleCase/4,tailleCase/4,QImage("../data/images/icones/1000.png").scaled(2*tailleCase,2*tailleCase));
                painter3.end();
                labelsPerso[6]->setPixmap(pixmap3);

                QPixmap pixmap4 = QPixmap(8.5*tailleCase,2.5*tailleCase);
                pixmap4.fill(Qt::transparent);
                QPainter painter4(&pixmap4);
                painter4.setFont(QFont("Times", (tailleCase/3)*142/dpi));
                painter4.setPen(QColor(255,255,255));
                painter4.drawText(QRectF(0,3,8.5*tailleCase -4 , 2.1*tailleCase), Qt::AlignCenter, "Change l'arme équipée");
                painter4.end();
                labelsPerso[7]->setPixmap(pixmap4);


                layoutPerso->addWidget(labelsPerso[6], 23, 2, 5,5);
                layoutPerso->addWidget(labelsPerso[7], 23, 7, 5,17);


                for(int i=1; i<6; i++)
                {
                    QPixmap pixmap = QPixmap(2.5*tailleCase,2.5*tailleCase);
                    pixmap.fill(Qt::transparent);
                    QPainter painter(&pixmap);
                    painter.setOpacity(0.75);
                    painter.drawImage(tailleCase/4,tailleCase/4,QImage("../data/images/icones/" + QString::number(-5 + 5*index + i) + ".png").scaled(2*tailleCase,2*tailleCase));
                    painter.end();
                    labelsPerso[6+2*i]->setPixmap(pixmap);

                    QPixmap pixmap2 = QPixmap(8.5*tailleCase,2.5*tailleCase);
                    pixmap2.fill(Qt::transparent);
                    QPainter painter2(&pixmap2);
                    painter2.setPen(QColor(255,255,255));
                    painter2.setFont(QFont("Times", (tailleCase/3)*142/dpi));


                    QString description = query.value(23+2*i).toString();

                    if(description.length() > 31)
                    {
                        int break1 = 31;
                        bool trouve = false;
                        while((break1>0) && (!trouve))
                        {
                            if(description[break1] == QChar(' '))
                            {
                                description.remove(break1);
                                description.insert(break1,"\n");
                                trouve = true;
                            }
                            else
                                break1--;
                        }
                        if(description.length() > break1 + 31)
                        {
                            int break2 = break1 + 31;
                            bool trouve = false;
                            while((break2>0) && (!trouve))
                            {
                                if(description[break2] == QChar(' '))
                                {
                                    description.remove(break2);
                                    description.insert(break2,"\n");
                                    trouve = true;
                                }
                                else
                                    break2--;
                            }
                        }
                    }

                    painter2.drawText(QRectF(0,3,8.5*tailleCase -4 , 2.1*tailleCase), Qt::AlignCenter, description);
                    painter2.end();
                    labelsPerso[7+2*i]->setPixmap(pixmap2);

                    if(i<3)
                    {
                        layoutPerso->addWidget(labelsPerso[6+2*i], 23+5*i, 2, 5,5);
                        layoutPerso->addWidget(labelsPerso[7+2*i], 23+5*i, 7, 5,17);
                    }
                    else
                    {
                        layoutPerso->addWidget(labelsPerso[6+2*i], 8+5*i, 33, 5,5);
                        layoutPerso->addWidget(labelsPerso[7+2*i], 8+5*i, 38, 5,17);
                    }
                }
            }

        }
        db.close();
    }
}

void MonLauncher::switchFenetres()
{
    if(animalShown)
    {
        layoutPrincipal->removeWidget(widgetAnimal);
        delete widgetAnimal;

        widgetPerso = new QWidget(this);
        widgetPerso->setLayout(layoutPerso);
        layoutPrincipal->addWidget(widgetPerso,0,0,42,56);
        animalShown = false;
        boutonSwitch->setText("Choisir un animal");
    }
    else
    {
        widgetAnimal = new MonChoixAnimal(this);
        layoutPrincipal->addWidget(widgetAnimal,0,0,42,56);
        animalShown = true;
        QObject::connect(widgetAnimal, SIGNAL(animalChanged(int)), this, SLOT(animalChanged(int)));
        boutonSwitch->setText("Choisir un personnage");
    }
}

void MonLauncher::newParticipant(QString participant, bool joueur)
{
    QLabel *label = new QLabel(this);
    label->setText(participant);
    label->setAlignment(Qt::AlignCenter);

    if(joueur)
    {
        label->setStyleSheet("width: " + QString::number(10*tailleCase) + "px; height: " + QString::number(1.5*tailleCase) + "px; background-color: rgba(0,162,232,200); border: 2px rgba(63,72,204,200) solid; font-size: " + QString::number(tailleCase) + "px; color: rgba(255,255,255,200);");
        nom = participant;
    }
    else
        label->setStyleSheet("width: " + QString::number(10*tailleCase) + "px; height: " + QString::number(1.5*tailleCase) + "px; background-color: rgba(127,127,127,200); border: 2px rgba(80,80,80,200) solid; font-size: " + QString::number(tailleCase) + "px; color: rgba(255,255,255,200);");

    participants.push_back(label);

    if(participants.length() <= 7)
        layoutPrincipal->addWidget(label, -1+4*participants.length(), 59, 3, 20);
}

void MonLauncher::deleteParticipant(QString participant)
{
    for(int i=0; i<participants.length(); i++)
    {
        if(participants[i]->text() == participant)
        {
            layoutPrincipal->removeWidget(participants[i]);
            delete participants.takeAt(i);

            if(i != participants.length())
            {
                for(int j=i; j<participants.length(); j++)
                {
                    layoutPrincipal->removeWidget(participants[j]);
                    layoutPrincipal->addWidget(participants[j], -1+4*(j+1), 59, 3, 20);
                }
            }
        }
    }
}

void MonLauncher::setPret()
{
    if(boutonPret->isChecked())
    {
        boutonPret->setStyleSheet("width: " + QString::number(6*tailleCase) + "px; height: " + QString::number(1*tailleCase) + "px; background-color: rgba(255,255,255,200); border: 1px solid rgba(40,40,40,200); border-radius: 2px; font-size: " + QString::number(tailleCase/2) + "px; color: rgba(40,40,40,200);");
        com->envoyer("c_pret(" + QString::number(qrand() % 10001) + "," + nom + "," + QString::number(group->checkedId()) + "," + QString::number(idAnimal) + ",1)");
        pret = true;

        if(animalShown)
            delete widgetAnimal;
    }
    else
    {
        pret = false;
        boutonPret->setStyleSheet("width: " + QString::number(6*tailleCase) + "px; height: " + QString::number(1*tailleCase) + "px; background-color: rgba(40,40,40,200); border: 1px solid rgba(255,255,255,200); border-radius: 2px; font-size: " + QString::number(tailleCase/2) + "px; color: rgba(255,255,255,200);");
        com->envoyer("c_pret(" + QString::number(qrand() % 10001) + "," + nom + "," + QString::number(group->checkedId()) + QString::number(idAnimal) + ",0)");
    }
}

void MonLauncher::start(int map)
{
    fenetre.chargerJeu(map, com);
    this->close();
}

void MonLauncher::reduire()
{
    setWindowState(Qt::WindowMinimized);
}

void MonLauncher::chooseMap()
{
    QVector<QPixmap> vecteur(0);
    vecteur.push_back(QPixmap("../data/images/launcher/maps/0.png"));
    vecteur.push_back(QPixmap("../data/images/launcher/maps/1.png"));
    vecteur.push_back(QPixmap("../data/images/launcher/maps/2.png"));
    vecteur.push_back(QPixmap("../data/images/launcher/maps/3.png"));
    vecteur.push_back(QPixmap("../data/images/launcher/maps/4.png"));
    vecteur.push_back(QPixmap("../data/images/launcher/maps/5.png"));
    slider = new ImageSlider(39*tailleCase,19.5*tailleCase,vecteur, this);
    QObject::connect(slider, SIGNAL(setMap(int)), this, SLOT(setMap(int)));

    layoutPrincipal->addWidget(slider, 1,1,78,39);
}

void MonLauncher::setMap(int mapRecu)
{
    com->setMap(mapRecu);
    layoutPrincipal->removeWidget(slider);
    delete slider;
}

void MonLauncher::animalChanged(int animalRecu)
{
    idAnimal = animalRecu;

    QVector<QString> texte(0);
    texte.push_back(" points de vie");
    texte.push_back(" points de mana");
    texte.push_back(" vitesse");
    texte.push_back(" de regénération de vie");
    texte.push_back(" de regénération de mana");
    texte.push_back(" % de dégats terre");
    texte.push_back(" % de dégats feu");
    texte.push_back(" % de dégats eau");
    texte.push_back(" % de dégats air");
    texte.push_back(" % de dégats");
    texte.push_back(" % de résistance terre");
    texte.push_back(" % de résistance feu");
    texte.push_back(" % de résistance eau");
    texte.push_back(" % de résistance air");
    texte.push_back(" % de résistance");
    texte.push_back(" % de dégats critiques");
    texte.push_back(" % de taux critique");
    texte.push_back(" % de chance d'assommer");
    texte.push_back(" % de réduction des temps de pause");

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../data/databases/animaux");
    db.open();
    bool trouve = false;
    QSqlQuery query(db);
    if(query.exec("SELECT * FROM animaux WHERE id=" + QString::number(animalRecu)))
    {
        while(query.next())
        {
            for(int i=0; i<19; i++)
            {
                if(query.value(i+1).toInt() > 0)
                {
                    trouve = true;
                    labelsPerso[19]->setText("+ " + QString::number(query.value(i+1).toInt()) + texte[i]);
                }
            }
            labelsPerso[21]->setPixmap(QPixmap("../data/images/launcher/animaux/" + QString::number(query.value(20).toInt()) + ".png").scaled(1.5*tailleCase,1.5*tailleCase));
        }
    }
    db.close();

    if(!trouve)
        labelsPerso[19]->setText("Aucun bonus apporté");
}
