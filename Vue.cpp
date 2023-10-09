#include "Vue.h"

Vue::Vue(QVector<Affichable*> *vecteurAffichablesRecu) : QWidget(), gotPerso(false), vecteurAnnonces(0)
{
    findParametres();

    this->setWindowIcon(QIcon("../data/images/icone.ico"));
    hasStarted = false;
    fini = false;

    vecteurAffichables = vecteurAffichablesRecu;

    fps = 40;
    sortShown = -1;
    drawParametres = false;

    qsrand(QDateTime::currentDateTime ().toTime_t ());

    lastRefresh.start();


    deplacementX = 0;
    deplacementY = 0;



    afficherHitboxes = false;

    QRect rec = QApplication::desktop()->screenGeometry();
    height = rec.height();
    width = rec.width();
    tailleCase = qMin(width / 40, int(height / 22.5));
    dpi = QApplication::desktop()->physicalDpiX();

    labelPrincipal = new QLabel(this);
    labelPrincipal->setMouseTracking(true);
    pixmapPrincipal = QPixmap(40*tailleCase, 21 * tailleCase);

    labelInterface = new QLabel(this);
    pixmapInterface = QPixmap (40*tailleCase, 1.5*tailleCase);
    labelInterface->setStyleSheet("margin-top: " + QString::number(height - 1.5*tailleCase) + "px; background: transparent;");


    layoutPrincipal = new QGridLayout(this);
    layoutPrincipal->addWidget(labelInterface, 0, 0, 1, 1);
    layoutPrincipal->addWidget(labelPrincipal, 0, 0, 1, 1);
    layoutPrincipal->setContentsMargins(0, 0, 0, 0);
    this->setStyleSheet("QWidget{background: black;}");
    this->setLayout(layoutPrincipal);

    timerAnnonce = new QTimer(this);
    timerAnnonce->setSingleShot(true);
    QObject::connect(timerAnnonce, SIGNAL(timeout()), this, SLOT(rafraichirAnnonce()));

    timerRefresh = new QTimer(this);
    timerRefresh->setSingleShot(true);
    QObject::connect(timerRefresh, SIGNAL(timeout()), this, SLOT(rafraichir()));

    consoleIsOn = false;
    parametresIsOn = false;
}

void Vue::start()
{
    hasStarted = true;
}

Vue::~Vue()
{
    delete timerAnnonce;
    delete timerRefresh;

    if(consoleIsOn)
    {
        console->close();
        delete console;
    }

    if(parametresIsOn)
        delete parametres;
}

void Vue::findParametres()
{
    raccourcis = QVector<int>(11,0);

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../data/databases/save");
    db.open();
    QSqlQuery query(db);
    if(query.exec("SELECT * FROM raccourcis"))
    {
        for(int i=0; i<11; i++)
        {
            query.next();
            raccourcis[i] = query.value(1).toInt();
        }
    }
}

void Vue::newRaccourcis(QVector<int> r)
{
    raccourcis = r;

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../data/databases/save");
    db.open();

    QSqlQuery query(db);
    for(int i=0; i<11; i++)
        query.exec("UPDATE raccourcis SET key=" + QString::number(raccourcis[i]) + " WHERE id=" + QString::number(i+1));

    deleteParametres();
}

void Vue::deleteParametres()
{
    if(parametresIsOn)
    {
        delete parametres;
        parametresIsOn = false;
    }
}

void Vue::rafraichirAnnonce()
{
    if((hasStarted) && (!fini))
    {
    if(vecteurAnnonces.length() > 0)
        vecteurAnnonces.removeFirst();

    rafraichir();

    if(vecteurAnnonces.length() > 0)
        timerAnnonce->start(2000);
    }
}

void Vue::ajouterAnnonce(QString annonce)
{
    if((hasStarted) && (!fini))
    {
    vecteurAnnonces.push_back(annonce.replace("lilou", "Lilou la plus belle ♥"));
    if(vecteurAnnonces.length() == 1)
    {
        rafraichir();
        timerAnnonce->start(3000);
    }
    }
}


void Vue::setPerso(Personnage *personnage)
{
    perso = personnage;
    gotPerso = true;
    rafraichirInterface();
    descriptionSorts = perso->getDescriptionSorts();
}

void Vue::setMap(Map *mapRecu)
{
    map = mapRecu;
    pixmapMap = QPixmap("../data/images/maps/map_" + QString::number(map->getNumero()) + ".png").scaled(map->getLargeur()*tailleCase, map->getHauteur()*tailleCase);
    labelPrincipal->setStyleSheet("margin-bottom: " + QString::number(1.5*tailleCase) + "px;");
}

void Vue::addWidget(QWidget *widget, int x, int y, int w, int h)
{
    layoutPrincipal->addWidget(widget, x, y, w, h);
}

void Vue::rafraichir()
{
    qDebug() << "Vue Rafraichir";
    if((hasStarted) && (!fini))
    {
        if(lastRefresh.elapsed() >= 1000/fps)
        {
            if(gotPerso)
            {
                pixmapPrincipal.fill(Qt::transparent);
                QPainter paint(&pixmapPrincipal);

                xMap = qMin(qMax(0.0, perso->getPosX() - 19), double(map->getLargeur()-40));
                yMap = qMin(qMax(0.0, perso->getPosY() - 10), double(map->getHauteur()-21));

                paint.drawPixmap(-tailleCase*xMap,-tailleCase*yMap,pixmapMap);//.copy(QRect(tailleCase*xMap, tailleCase*yMap, 40*tailleCase, 21*tailleCase))));
                //paint.drawPixmap(0,0,QPixmap(pixmapMap.copy(QRect(tailleCase*xMap, tailleCase*yMap, 40*tailleCase, 21*tailleCase))));

                QPen pen(QColor(0,0,0));
                paint.setPen(pen);
                paint.setFont(QFont("Times", (0.15 * tailleCase)*142/dpi));


                for(int i=0; i<vecteurAffichables->length(); i++)
                {
                    Affichable *affichable = vecteurAffichables->value(i);
                    if((affichable != nullptr) && (*affichable == 1))
                    {
                        double posX = affichable->getPosXAffichage();
                        double posY = affichable->getPosYAffichage();
                        double tailleX = affichable->getTailleX();
                        double tailleY = affichable->getTailleY();
                        if((posX + tailleX > xMap) && (posY + tailleY > yMap) && (posX - tailleX < xMap + 40) && (posY - tailleY < yMap + 21))
                        {
                            if(Animal* animal = dynamic_cast<Animal*>(affichable))
                            {
                                if(animal->isInvisible())
                                {
                                    if(animal->getMaitre() == perso->getNom())
                                    {
                                        paint.setOpacity(0.5);
                                        paint.drawImage(tailleCase * (posX-xMap), tailleCase * (posY-yMap), affichable->getSprite()->scaled(tailleX*tailleCase, tailleY*tailleCase));
                                        paint.setOpacity(1);
                                    }
                                }
                                else
                                    paint.drawImage(tailleCase * (posX-xMap), tailleCase * (posY-yMap), affichable->getSprite()->scaled(tailleX*tailleCase, tailleY*tailleCase));
                            }
                            else if(Personnage* personnage = dynamic_cast<Personnage*>(affichable))
                            {
                                if(personnage->isInvisible())
                                {
                                    if(personnage->getNom() == perso->getNom())
                                    {
                                        paint.setOpacity(0.5);
                                        paint.drawImage(tailleCase * (posX-xMap), tailleCase * (posY-yMap), affichable->getSprite()->scaled(tailleX*tailleCase, tailleY*tailleCase));
                                        paint.setOpacity(1);
                                        pen.setWidth(1);
                                        paint.setPen(pen);
                                        paint.setBrush(QColor(80,80,80,230));
                                        paint.drawRoundedRect(QRectF((posX-xMap +0.16) * tailleCase, (posY-yMap - 0.2 ) * tailleCase, 1 * tailleCase, 0.16 * tailleCase), 0.07*tailleCase, 0.07*tailleCase);
                                        paint.fillRect(QRectF((posX-xMap +0.18) * tailleCase + 1, (posY-yMap - 0.19 ) * tailleCase + 1, personnage->getVie()/double(personnage->getStats()[0])*(0.96 * tailleCase - 2), 0.06 * tailleCase), QColor(200,0,0));
                                        paint.fillRect(QRectF((posX-xMap +0.18) * tailleCase + 1, (posY-yMap - 0.10 ) * tailleCase + 1, personnage->getMana()/double(personnage->getStats()[1])*(0.96 * tailleCase - 2), 1), QColor(0,0,255));
                                        pen.setColor(QColor(0,0,0));
                                        paint.setPen(pen);
                                        paint.drawText(QRectF((posX-xMap-0.4) * tailleCase, (posY-yMap - 0.5 ) * tailleCase, 2.13 * tailleCase, 0.2 * tailleCase), Qt::AlignCenter, personnage->getNom().replace("lilou", "Lilou la plus belle ♥"));
                                        paint.setOpacity(1);
                                    }
                                }
                                else
                                {
                                    paint.drawImage(tailleCase * (posX-xMap), tailleCase * (posY-yMap), affichable->getSprite()->scaled(tailleX*tailleCase, tailleY*tailleCase));
                                    pen.setWidth(1);
                                    pen.setColor(QColor(0,0,0));
                                    paint.setPen(pen);
                                    paint.setBrush(QColor(80,80,80,230));
                                    paint.drawRoundedRect(QRectF((posX-xMap +0.16) * tailleCase, (posY-yMap - 0.2 ) * tailleCase, 1 * tailleCase, 0.16 * tailleCase), 0.07*tailleCase, 0.07*tailleCase);
                                    paint.fillRect(QRectF((posX-xMap +0.18) * tailleCase + 1, (posY-yMap - 0.19 ) * tailleCase + 1, personnage->getVie()/double(personnage->getStats()[0])*(0.96 * tailleCase - 2), 0.06 * tailleCase), QColor(200,0,0));
                                    paint.fillRect(QRectF((posX-xMap +0.18) * tailleCase + 1, (posY-yMap - 0.10 ) * tailleCase + 1, personnage->getMana()/double(personnage->getStats()[1])*(0.96 * tailleCase - 2), 1), QColor(0,0,255));
                                    pen.setColor(QColor(0,0,0));
                                    paint.setPen(pen);
                                    paint.drawText(QRectF((posX-xMap-0.4) * tailleCase, (posY-yMap - 0.5 ) * tailleCase, 2.13 * tailleCase, 0.2 * tailleCase), Qt::AlignCenter, personnage->getNom().replace("lilou", "Lilou la plus belle ♥"));


                                    if(personnage->isStun())
                                    {
                                        pen.setWidth(1);
                                        pen.setColor(QColor(255,255,255));
                                        paint.setPen(pen);
                                        paint.drawText(QRectF((posX-xMap-0.05) * tailleCase, (posY-yMap) * tailleCase, 1.4 * tailleCase, 0.2 * tailleCase), Qt::AlignCenter, "assommé");
                                        paint.drawLine(QPoint((posX-xMap+0.15) * tailleCase,(posY-yMap+0.25) * tailleCase), QPoint((posX-xMap+0.15 + 1*double(perso->getTempsStun())/2000)*tailleCase,(posY-yMap+0.25) * tailleCase));
                                    }
                                }
                            }
                            else
                            {
                                paint.drawImage(tailleCase * (posX-xMap), tailleCase * (posY-yMap), affichable->getSprite()->scaled(tailleX*tailleCase, tailleY*tailleCase));
                            }


                            if(afficherHitboxes)
                            {
                                QRectF rectangle = affichable->getHitbox();
                                paint.drawRect(QRect((rectangle.x()-xMap) * tailleCase, (rectangle.y()-yMap) * tailleCase, rectangle.width() * tailleCase, rectangle.height() * tailleCase));
                            }
                        }
                    }
                    else
                    {
                        emit addToConsole(QColor(180,110,75), "Collision", "affichable already deleted", true, true);
                        vecteurAffichables->removeOne(affichable);
                        emit addToConsole(QColor(180,110,75), "Collision", "affichable remove from vecteur", true, true);
                    }
                }

                paint.setPen(QColor(255, 0, 0));
                if(afficherHitboxes)
                {
                    QVector<QRectF> *obstacles = map->getObstacles();
                    for(int i=0; i<obstacles->length(); i++)
                    {
                        QRectF rectangle = obstacles->value(i);
                        paint.drawRect(QRect((rectangle.x()-xMap) * tailleCase, (rectangle.y()-yMap) * tailleCase, rectangle.width() * tailleCase, rectangle.height() * tailleCase));
                    }
                }


                paint.setPen(QColor(80,80,80));
                paint.setFont(QFont("Times", (0.5*tailleCase)*142/dpi));

                if(vecteurAnnonces.length() > 0)
                {
                    paint.setBrush(QColor(40,40,40,100));
                    paint.setPen(QColor(40,40,40,100));
                    paint.drawRoundedRect(QRect((20-sqrt(vecteurAnnonces[0].length())*1.2)*tailleCase, 2.8*tailleCase, (sqrt(vecteurAnnonces[0].length())*2*1.2)*tailleCase, 1.5*tailleCase), 0.1*tailleCase, 0.1*tailleCase);

                    QFont font("Times", (0.5*tailleCase)*142/dpi);
                    paint.setPen(QColor(0,0,0,220));
                    paint.setFont(font);
                    paint.drawText(QRect(0.2, 3.1*tailleCase, width, tailleCase), Qt::AlignCenter, vecteurAnnonces[0]);

                    paint.setPen(QColor(250,250,250, 220));
                    paint.drawText(QRect(0, 3*tailleCase, width, tailleCase), Qt::AlignCenter, vecteurAnnonces[0]);
                }



                if(!perso->estVivant())
                {
                    rafraichirInterface();
                    paint.setPen(QColor(200,0,0, 127));
                    paint.fillRect(QRect(0,0,width,height), QColor(200,0,0, 127));

                    paint.setPen(QColor(255,255,255));
                    paint.setFont(QFont("Times", (1*tailleCase)*142/dpi));
                    paint.drawText(QRect(0,0,width,height), Qt::AlignCenter, "Vous êtes mort");

                    paint.setFont(QFont("Times", (0.5*tailleCase)*142/dpi));
                    paint.drawText(QRect(0,1.75*tailleCase,width,height), Qt::AlignCenter, "Mort(s) restante(s) : "  + QString::number(3 - perso->getMort()));
                }

                if(drawParametres)
                {
                    paint.setPen(QColor(10,10,10, 10));
                    paint.fillRect(QRect(0,0,width,height), QColor(0,0,0, 127));

                    paint.setPen(QColor(180,180,180,220));
                    paint.setBrush(QColor(20,20,20,220));
                    paint.drawRoundedRect(QRect(15*tailleCase,9*tailleCase, 9*tailleCase, 0.8*tailleCase), 0.1*tailleCase, 0.1*tailleCase);
                    paint.drawRoundedRect(QRect(15*tailleCase,10*tailleCase, 9*tailleCase, 0.8*tailleCase), 0.1*tailleCase, 0.1*tailleCase);
                    paint.drawRoundedRect(QRect(15*tailleCase,11*tailleCase, 9*tailleCase, 0.8*tailleCase), 0.1*tailleCase, 0.1*tailleCase);

                    paint.setPen(QColor(180,180,180,220));
                    paint.setFont(QFont("Times", (0.33*tailleCase)*142/dpi));
                    paint.drawText(QRect(15*tailleCase,9*tailleCase, 9*tailleCase, 0.8*tailleCase), Qt::AlignCenter, "Retour");
                    paint.drawText(QRect(15*tailleCase,10*tailleCase, 9*tailleCase, 0.8*tailleCase), Qt::AlignCenter, "Choisir les contrôles");
                    paint.drawText(QRect(15*tailleCase,11*tailleCase, 9*tailleCase, 0.8*tailleCase), Qt::AlignCenter, "Quitter le jeu");
                }

                if(sortShown != -1)
                {
                    paint.setPen(QPen(QColor(80,80,80,200), 6));
                    paint.setBrush(QColor(0,0,0,200));
                    paint.drawRect(QRectF(12*tailleCase,17.7*tailleCase,10*tailleCase,2.3*tailleCase));

                    paint.setPen(QColor(255,201,14));
                    paint.setFont(QFont("Times", (0.33*tailleCase)*142/dpi));
                    paint.drawText(QRectF(12.5*tailleCase,17.9*tailleCase,9*tailleCase,1.5*tailleCase), Qt::AlignLeft, descriptionSorts[2*sortShown]);
                    paint.setFont(QFont("Times", (0.18*tailleCase)*142/dpi));
                    paint.drawText(QRectF(12.5*tailleCase,17.9*tailleCase,9*tailleCase,0.3*tailleCase), Qt::AlignRight, QString::number(perso->getVecteurSorts()->value(sortShown)->getCooldown()) + " secondes");

                    paint.setPen(QColor(63,72,204));
                    paint.drawText(QRectF(12.5*tailleCase,18.2*tailleCase,9*tailleCase,0.3*tailleCase), Qt::AlignRight, QString::number(perso->getVecteurSorts()->value(sortShown)->getCoutMana()) + " mana");

                    paint.setPen(QColor(255,255,255));
                    paint.setFont(QFont("Times", (0.25*tailleCase)*142/dpi));
                    paint.drawText(QRectF(12.5*tailleCase,18.7*tailleCase,9*tailleCase,1.5*tailleCase), descriptionSorts[1+2*sortShown]);
                }

                paint.end();
                labelPrincipal->setPixmap(pixmapPrincipal);
                lastRefresh.start();
                addToConsole(Qt::blue, "Vue", "Rafraichir", true, false);
                }
            }
            else
            {
                if(!timerRefresh->isActive())
                    timerRefresh->start(1000/fps-lastRefresh.elapsed());
        }
    }
    else
    {
        if(!fini)
        {
            pixmapPrincipal.fill(Qt::transparent);
            QPainter paint(&pixmapPrincipal);
            paint.setPen(QColor(255,255,255));
            paint.setFont(QFont("Times", (0.5*tailleCase)*142/dpi));
            paint.drawText(QRect(0,0,width,height), Qt::AlignCenter, "En attente des joueurs...");
            paint.end();
            labelPrincipal->setPixmap(pixmapPrincipal);
        }
    }
}

void Vue::rafraichirInterface()
{
    if((hasStarted) && (!fini))
    {
        QVector<Sort*>* vecteurSorts = perso->getVecteurSorts();
        pixmapInterface.fill(Qt::transparent);
        QPainter painter(&pixmapInterface);
        painter.setFont(QFont("times", (tailleCase/3)*142/dpi));
        painter.drawImage(1*tailleCase, 0.25*tailleCase, QImage("../data/images/faces/" + QString::number(perso->getType()) + ".png").scaled(tailleCase, tailleCase));
        painter.setPen(QPen(QColor(80,80,80), 3));
        painter.drawRoundedRect(QRect(1*tailleCase-2, 0.25*tailleCase-2, tailleCase+2, tailleCase +2),2,2);

        painter.setPen(QColor(255,255,255));
        painter.setFont(QFont("Times", (tailleCase/3)*142/dpi));
        painter.drawText(QRect(2.5*tailleCase, 0.25*tailleCase, 10*tailleCase,0.65*tailleCase), perso->getNom());

        painter.setPen(QColor(255,201,14));
        painter.setFont(QFont("Times", (tailleCase/5)*142/dpi));
        painter.drawText(QRect(2.5*tailleCase, 0.90*tailleCase, 10*tailleCase,0.4*tailleCase), perso->getClasse());


        for(int i=0; i<vecteurSorts->length(); i++)
        {
            painter.drawImage(QRectF((12.5+1.5*i)*tailleCase, 0.25*tailleCase, tailleCase, tailleCase), QImage("../data/images/icones/" + QString::number(vecteurSorts->value(i)->getIcone()) + ".png").scaled(tailleCase, tailleCase));
            if(ChangerArme* sort = dynamic_cast<ChangerArme*>(vecteurSorts->value(i)))
                painter.drawImage(QRectF((12.5+1.5*i)*tailleCase, 0.25*tailleCase, tailleCase, tailleCase), QImage("../data/images/armes/" + QString::number(perso->getArme()->getIcone()) + ".png").scaled(tailleCase, tailleCase));

            if(vecteurSorts->value(i)->isOnCd())
            {
                painter.setBrush(QColor(0, 0, 0, 127));
                painter.setPen(Qt::transparent);
                painter.drawPie(QRectF((12.25 + 1.5*i)*tailleCase, 0, 1.5*tailleCase, 1.5*tailleCase), 90*16, 360*16*(vecteurSorts->value(i)->getCooldownRemaining() / vecteurSorts->value(i)->getCooldown()));
                painter.setFont(QFont("Times", (tailleCase/3)*142/dpi));
                painter.setPen(QColor(255, 255, 255));
                painter.drawText((12.5+1.5*i)*tailleCase, 0.25*tailleCase, tailleCase, tailleCase, Qt::AlignCenter, QString::number(int(vecteurSorts->value(i)->getCooldownRemaining()+0.8)));
            }
            painter.setPen(QColor(200,200,200,200));
            painter.setBrush(QColor(200,200,200,200));
            painter.drawRect(QRectF((13.15+1.5*i)*tailleCase, 0.9*tailleCase, 0.3*tailleCase, 0.3*tailleCase));

            painter.setPen(QColor(0,0,0, 200));
            painter.setFont(QFont("Times", (tailleCase/6)*142/dpi));

            if(i != 0)
                painter.drawText(QRectF((13.15+1.5*i)*tailleCase, 0.9*tailleCase, 0.3*tailleCase, 0.3*tailleCase), Qt::AlignCenter, QString::number(i));
            else
                painter.drawText(QRectF((13.15+1.5*i)*tailleCase, 0.9*tailleCase, 0.3*tailleCase, 0.3*tailleCase), Qt::AlignCenter, "A");
        }

        // Fond Vie
        painter.setPen(QColor(0,0,0));
        painter.setBrush(QColor(150,0,0));
        painter.drawRoundedRect(QRectF(28.9*tailleCase, 0.2*tailleCase, 10.1 * tailleCase, 0.5*tailleCase), 0.1*tailleCase, 0.1*tailleCase);

        // Fond Mana
        painter.setBrush(QColor(0,0,150));
        painter.drawRoundedRect(QRectF(28.9*tailleCase, 0.8*tailleCase, 10.1 * tailleCase, 0.5*tailleCase), 0.1*tailleCase, 0.1*tailleCase);

        // Barre Vie
        painter.setPen(QColor(150,0,0));
        painter.setBrush(QColor(220,0,0));
        painter.drawRoundedRect(QRectF(28.95*tailleCase, 0.25*tailleCase, perso->getVie()/double(perso->getStats()[0]) * 10 * tailleCase, 0.4*tailleCase), 0.1*tailleCase, 0.1*tailleCase);

        // Barre Mana
        painter.setPen(QColor(0,0,150));
        painter.setBrush(QColor(0,0,220));
        painter.drawRoundedRect(QRectF(28.95*tailleCase, 0.85*tailleCase, perso->getMana()/double(perso->getStats()[1]) * 10 * tailleCase, 0.4*tailleCase), 0.1*tailleCase, 0.1*tailleCase);

        // Texte Vie
        painter.setPen(QColor(255,255,255,200));
        painter.setFont(QFont("times", (tailleCase/5)*142/dpi));
        painter.drawText(QRectF(28.95*tailleCase, 0.25*tailleCase, 10 * tailleCase, 0.4*tailleCase), Qt::AlignCenter, QString::number(perso->getVie()) + " / " + QString::number(perso->getStats()[0]));

        // Texte Mana
        painter.drawText(QRectF(28.95*tailleCase, 0.85*tailleCase, 10 * tailleCase, 0.4*tailleCase), Qt::AlignCenter, QString::number(perso->getMana()) + " / " + QString::number(perso->getStats()[1]));


        painter.end();
        labelInterface->setPixmap(pixmapInterface);
        addToConsole(Qt::blue, "Vue", "Rafraichir interface", true, false);
    }
}


/* SIGNAL qui permet de detecter l'appui d'une touche
 * Reçoit automatiquement un QKeyEvent */

void Vue::keyPressEvent (QKeyEvent *event)
{
    if((hasStarted) && (!fini))
    {
    if(!(event->isAutoRepeat()))
    {
        touches.push_back(event->key());
        QPoint pos = this->mapFromGlobal(QCursor::pos());
        double x = static_cast<double>(static_cast<int>(double(pos.x())/tailleCase*10+0.5))/10.0;
        double y = static_cast<double>(static_cast<int>(double(pos.y())/tailleCase*10+0.5))/10.0;

        addToConsole(Qt::blue, "Vue", "keyPressed = " + QString::number(event->key()), true, true);

        toucheAppuyee(touches.last(), x, y);

        switch(event->key())
        {
            case 16777266: // F3
            afficherHitboxes = !afficherHitboxes;
            break;

            case 16777267: // F4
            if(consoleIsOn)
                delete console;
            else
                console = new Console(width, height, true);

            consoleIsOn = !consoleIsOn;
            break;

            case 16777268: // F5
            if(consoleIsOn)
                delete console;
            else
                console = new Console(width, height, false);

            consoleIsOn = !consoleIsOn;
        }
    }
    }
}

void Vue::toucheAppuyee(int key, double x, double y)
{
    if((hasStarted) && (!fini))
    {
    if(key == 16777216) // Echap
    {
        drawParametres = !drawParametres;
        rafraichir();
    }
    else if(key == raccourcis[7]) // Z
    {
        emit signalDeplacer(0,-1);
        deplacementX = 0;
        deplacementY = -1;
    }
    else if(key == raccourcis[10]) // D
    {
        emit signalDeplacer(1,0);
        deplacementX = 1;
        deplacementY = 0;
    }
    else if(key == raccourcis[9]) // S
    {
        emit signalDeplacer(0,1);
        deplacementX = 0;
        deplacementY = 1;
    }

    else if(key == raccourcis[8]) // Q
    {
        emit signalDeplacer(-1,0);
        deplacementX = -1;
        deplacementY = 0;
    }
    else if(key == raccourcis[5]) // Espace
    {
        emit signalAttaquer(perso->getNom());
        //emit envoyer("a(" + QString::number(qrand() % 10001) + "," + perso->getNom() + ")");
    }
    else if(key == raccourcis[6])
    {
        addToConsole(Qt::blue, "Vue", "ChangerArme", true, true);
        emit signalCastSort(perso->getNom(), 0, x+xMap, y+yMap);
        //emit envoyer("s(" + QString::number(qrand() % 10001) + "," + perso->getNom() + ",0," + QString::number(x+xMap) + "," + QString::number(y+yMap) + ")");
    }
    else if(key == raccourcis[0])
    {
        addToConsole(Qt::blue, "Vue", "Sort 1", true, true);
        emit signalCastSort(perso->getNom(), 1, x+xMap, y+yMap);
        //emit envoyer("s(" + QString::number(qrand() % 10001) + "," + perso->getNom() + ",1," + QString::number(x+xMap) + "," + QString::number(y+yMap) + ")");
    }
    else if(key == raccourcis[1])
    {
        addToConsole(Qt::blue, "Vue", "Sort 2", true, true);
        emit signalCastSort(perso->getNom(), 2, x+xMap, y+yMap);
        //emit envoyer("s(" + QString::number(qrand() % 10001) + "," + perso->getNom() + ",2," + QString::number(x+xMap) + "," + QString::number(y+yMap) + ")");
    }
    else if(key == raccourcis[2])
    {
        addToConsole(Qt::blue, "Vue", "Sort 3", true, true);
        emit signalCastSort(perso->getNom(), 3, x+xMap, y+yMap);
        //emit envoyer("s(" + QString::number(qrand() % 10001) + "," + perso->getNom() + ",3," + QString::number(x+xMap) + "," + QString::number(y+yMap) + ")");
    }

    else if(key == raccourcis[3])
    {
        addToConsole(Qt::blue, "Vue", "Sort 4", true, true);
        emit signalCastSort(perso->getNom(), 4, x+xMap, y+yMap);
        //emit envoyer("s(" + QString::number(qrand() % 10001) + "," + perso->getNom() + ",4," + QString::number(x+xMap) + "," + QString::number(y+yMap) + ")");
    }

    else if(key == raccourcis[4])
    {
        addToConsole(Qt::blue, "Vue", "Sort 5", true, true);
        emit signalCastSort(perso->getNom(), 5, x+xMap, y+yMap);
        //emit envoyer("s(" + QString::number(qrand() % 10001) + "," + perso->getNom() + ",5," + QString::number(x+xMap) + "," + QString::number(y+yMap) + ")");;
    }
    }

}

void Vue::keyReleaseEvent (QKeyEvent *event)
{
    if((hasStarted) && (!fini))
    {
    if(!(event->isAutoRepeat()))
    {
        int key = event->key();
        touches.removeOne(key);
        if((key == raccourcis[7]) || (key == raccourcis[8]) || (key == raccourcis[9]) || (key == raccourcis[10]))
        {
            emit signalDeplacer(0,0);
            deplacementX = 0;
            deplacementY = 0;
        }

        if(touches.length() > 0)
        {
            qDebug() << "autorepeat" <<touches.last() ;
            QPoint pos = this->mapFromGlobal(QCursor::pos());
            double x = double(pos.x())/tailleCase;
            double y = double(pos.y())/tailleCase;

            toucheAppuyee(touches.last(), x, y);
        }
    }
    }
}

void Vue::mouseReleaseEvent (QMouseEvent* event)
{
    if((hasStarted) && (!fini))
    {
        int key = event->button();
        touches.removeOne(key);
        if((key == raccourcis[7]) || (key == raccourcis[8]) || (key == raccourcis[9]) || (key == raccourcis[10]))
        {
            emit signalDeplacer(0,0);
            deplacementX = 0;
            deplacementY = 0;
        }

        if(touches.length() > 0)
        {
            qDebug() << "autorepeat" <<touches.last() ;
            QPoint pos = this->mapFromGlobal(QCursor::pos());
            double x = double(pos.x())/tailleCase;
            double y = double(pos.y())/tailleCase;

            toucheAppuyee(touches.last(), x, y);
        }
    }
}

void Vue::mousePressEvent(QMouseEvent* event)
{
    QPoint pos = this->mapFromGlobal(QCursor::pos());
    double x = static_cast<double>(static_cast<int>(double(pos.x())/tailleCase*10+0.5))/10.0;
    double y = static_cast<double>(static_cast<int>(double(pos.y())/tailleCase*10+0.5))/10.0;
    addToConsole(Qt::blue, "Vue", "mousePressed at X = " + QString::number(pos.x()) + "   / Y = " + QString::number(pos.y()), true, true);
    int tailleX = width /40;
    int tailleY = height / 22.5;
    if((hasStarted) && (!fini))
    {


    int previousSortShown = sortShown;
    sortShown = -1;
    for(int i=0; i<6; i++)
    {
        if(QRectF((12.5+1.5*i)*tailleX, 21.25*tailleY, tailleX, tailleY).contains(pos))
        {
            sortShown = i;
            rafraichir();
        }
    }

    if((sortShown == -1) && (previousSortShown != -1))
        rafraichir();

    if(drawParametres)
    {
        if(QRect(15*tailleX, 9*tailleY, 9*tailleX, 0.8*tailleY).contains(pos))
        {
            drawParametres = !drawParametres;
            rafraichir();
        }

        if(QRect(15*tailleX, 10*tailleY, 9*tailleX, 0.8*tailleY).contains(pos))
        {
            if(!parametresIsOn)
            {
                //setFocusPolicy(Qt::);
                parametres = new Parametres(raccourcis, this);
                QObject::connect(parametres, SIGNAL(newKeys(QVector<int>)), this, SLOT(newRaccourcis(QVector<int>)));
                QObject::connect(parametres, SIGNAL(deleteParametres()), this, SLOT(deleteParametres()));
                parametres->show();
                parametres->move(QPoint((width-650)/2, (height-500)/2));
                parametresIsOn = true;
            }
        }

        if(QRect(15*tailleX, 11*tailleY, 9*tailleX, 0.8*tailleY).contains(pos))
            this->close();
    }
    else
    {
        int key = event->button();
        touches.push_back(key);
        QPoint pos = this->mapFromGlobal(QCursor::pos());
        double x = static_cast<double>(static_cast<int>(double(pos.x())/tailleCase*10+0.5))/10.0;
        double y = static_cast<double>(static_cast<int>(double(pos.y())/tailleCase*10+0.5))/10.0;

        addToConsole(Qt::blue, "Vue", "keyPressed = " + QString::number(key), true, true);

        toucheAppuyee(touches.last(), x, y);
    }
    }

    if(fini)
    {
        if(QRect(18.5*tailleX,11.5*tailleY, 3*tailleX, 0.5*tailleY).contains(pos))
            this->close();
    }
}

void Vue::victoire()
{
    qDebug() << "Vue victoire";
    addToConsole(Qt::blue, "Vue", "Victoire", true, true);

    hasStarted = false;
    fini = true;

    QPainter paint(&pixmapPrincipal);
    paint.drawImage(0, 0, QImage("../data/images/victoire.png").scaled(40*tailleCase, 21*tailleCase));

    paint.setPen(QColor(180,180,180,220));
    paint.setBrush(QColor(20,20,20,220));
    paint.drawRoundedRect(QRect(18.5*tailleCase,11.5*tailleCase, 3*tailleCase, 0.7*tailleCase), 0.1*tailleCase, 0.1*tailleCase);

    paint.setPen(QColor(255,255,255,220));
    paint.setFont(QFont("Times", (0.28*tailleCase)*142/dpi));
    paint.drawText(QRect(18.5*tailleCase,11.5*tailleCase, 3*tailleCase, 0.7*tailleCase), Qt::AlignCenter, "Quitter");
    paint.end();
    labelPrincipal->setPixmap(pixmapPrincipal);
    timerRefresh->stop();
    qDebug() << "Vue finVictoire";
}

void Vue::defaite()
{
    addToConsole(Qt::blue, "Vue", "Defaite", true, true);

    hasStarted = false;
    fini = true;

    QPainter paint(&pixmapPrincipal);
    paint.drawImage(14.4*tailleCase, 6.7*tailleCase, QImage("../data/images/defaite.png").scaled(11*tailleCase, 5*tailleCase));

    paint.setPen(QColor(180,180,180,220));
    paint.setBrush(QColor(20,20,20,220));
    paint.drawRoundedRect(QRect(18.5*tailleCase,11.5*tailleCase, 3*tailleCase, 0.7*tailleCase), 0.1*tailleCase, 0.1*tailleCase);

    paint.setPen(QColor(255,255,255,220));
    paint.setFont(QFont("Times", (0.28*tailleCase)*142/dpi));
    paint.drawText(QRect(18.5*tailleCase,11.5*tailleCase, 3*tailleCase, 0.7*tailleCase), Qt::AlignCenter, "Quitter");
    paint.end();
    labelPrincipal->setPixmap(pixmapPrincipal);
    timerRefresh->stop();
}


void Vue::addToConsole(QColor couleur, QString source, QString message, bool newLine, bool important)
{
    if((hasStarted) && (!fini))
    {
    if(consoleIsOn)
        console->add(couleur,source,message,newLine, important);
    }
}
