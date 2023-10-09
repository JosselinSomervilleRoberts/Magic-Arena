#include "Vivants/Personnage.h"

Personnage::Personnage(bool persoPrincipalRecu, int typeRecu, QString nomRecu, Map *mapRecu, Collision *collisionRecu) : Vivant(), collision(collisionRecu)
{
    gotAnimal = false;
    descriptionSorts = QVector<QString>(12, "");

    player = new QMediaPlayer(this);
    player->setVolume(25);
    player->setMedia(QUrl::fromLocalFile("../data/musiques/animations/footstep_gravier.wav"));

    persoPrincipal = persoPrincipalRecu;

    mort = 0;
    timerMort = new QTimer(this);
    estMort = false;

    timerMort->setSingleShot(true);
    QObject::connect(timerMort, SIGNAL(timeout()), this, SLOT(revivre()));

    type = typeRecu;
    invisible = false;
    stun = false;

    nom = nomRecu;
    map = mapRecu;

    tailleX = (1.33);
    tailleY = (1.33);

    findSave(type);
    action = -1;
    actionSprite = 1;
    orientation = 2;
    etape = 0;

    sorts = new QVector<Sort*>();

    ChangerArme *change = new ChangerArme(this->getNom(), &stats, collision);
    QObject::connect(change, SIGNAL(changerArme()), this, SLOT(changerArme()));
    sorts->push_back(change);

    sortFleche = new S_Fleche(&arme, this->getNom(), &stats, collision, &posX, &posY, &orientation);
    QObject::connect(sortFleche, SIGNAL(ajouterAffichable(Affichable*)), this, SLOT(ajoutAffichable(Affichable*)));
    sortDegatsArme = new S_DegatsArme(arme, this->getNom(), &stats, collision, &posX, &posY, &orientation);
    QObject::connect(sortDegatsArme, SIGNAL(ajouterAffichable(Affichable*)), this, SLOT(ajoutAffichable(Affichable*)));


    if(type == 1)
    {
        S_Assassinat *assassinat = new S_Assassinat(this->getNom(), &stats, collision, &posX, &posY, &orientation);
        sorts->push_back(assassinat);
        QObject::connect(assassinat, SIGNAL(envoyer(QString)), this, SLOT(envoyerMessage(QString)));

        S_Invisibilite *invisibilite = new S_Invisibilite(this->getNom(), &stats, collision, &posX, &posY);
        sorts->push_back(invisibilite);
        QObject::connect(invisibilite, SIGNAL(setInvisible(bool)), this, SLOT(setInvisible(bool)));

        S_WindWalk *walk = new S_WindWalk(this->getNom(), &stats, collision, &posX, &posY);
        sorts->push_back(walk);

        S_Piege *piege = new S_Piege(this->getNom(), &stats, collision);
        sorts->push_back(piege);

        S_ApotreMort *mort = new S_ApotreMort(this->getNom(), &stats, collision, &posX, &posY);
        sorts->push_back(mort);
    }
    else if(type == 2)
    {
        S_Vampirisme *vampire = new S_Vampirisme(this->getNom(), &stats, collision, &posX, &posY, &vie);
        sorts->push_back(vampire);
        QObject::connect(vampire, SIGNAL(ajouterVie(int)), this, SLOT(ajouterVie(int)));

        S_Teleportation *tp = new S_Teleportation(this->getNom(), &stats, collision, &posX, &posY);
        sorts->push_back(tp);
        QObject::connect(tp, SIGNAL(teleporter(double,double,int)), this, SLOT(setPos(double,double,int)));

        S_DarkField *field = new S_DarkField(this->getNom(), &stats, collision, &posX, &posY);
        sorts->push_back(field);

        S_DarkCage *cage = new S_DarkCage(this->getNom(), &stats, collision);
        sorts->push_back(cage);
        QObject::connect(cage, SIGNAL(add(QVector<QRectF>)), map, SLOT(ajouterObstacles(QVector<QRectF>)));
        QObject::connect(cage, SIGNAL(remove(QVector<QRectF>)), map, SLOT(retirerObstacles(QVector<QRectF>)));

        S_BlackHoleDark *blackHole = new S_BlackHoleDark(this->getNom(), &stats, collision);
        sorts->push_back(blackHole);
    }
    else if(type == 3)
    {
        S_DiffusionLumiere *diffusionLumiere = new S_DiffusionLumiere(this->getNom(), &stats, collision, &posX, &posY);
        sorts->push_back(diffusionLumiere);

        S_LumiereBrulante *lumiereBrulante = new S_LumiereBrulante(this->getNom(), &stats, collision);
        sorts->push_back(lumiereBrulante);

        S_Heal *heal = new S_Heal(this->getNom(), &stats, collision, &posX, &posY);
        sorts->push_back(heal);
        QObject::connect(heal, SIGNAL(ajouterVie(int)), this, SLOT(ajouterVie(int)));

        S_LumiereDivine *divine = new S_LumiereDivine(this->getNom(), &stats, collision, &posX, &posY);
        sorts->push_back(divine);

        S_Light *light = new S_Light(this->getNom(), &stats, collision, &posX, &posY);
        sorts->push_back(light);
        QObject::connect(light, SIGNAL(stun(bool)), this, SLOT(setStun(bool)));
    }
    else if(type == 4)
    {
        S_ExplosionTerre *terre = new S_ExplosionTerre(this->getNom(), &stats, collision, &posX, &posY);
        sorts->push_back(terre);

        S_ExplosionFeu *feu = new S_ExplosionFeu(this->getNom(), &stats, collision, &posX, &posY);
        sorts->push_back(feu);

        S_ExplosionGlace *eau = new S_ExplosionGlace(this->getNom(), &stats, collision, &posX, &posY);
        sorts->push_back(eau);

        S_ExplosionAir *vent = new S_ExplosionAir(this->getNom(), &stats, collision, &posX, &posY);
        sorts->push_back(vent);

        S_DiffusionMulti *diffusion = new S_DiffusionMulti(this->getNom(), &stats, collision, &posX, &posY);
        sorts->push_back(diffusion);

        //S_LaserEau *laser = new S_LaserEau(this->getNom(), &stats, collision, &posX, &posY, &orientation);
        //sorts->push_back(laser);

        QObject::connect(terre, SIGNAL(explosion()), feu, SLOT(stop()));
        QObject::connect(terre, SIGNAL(explosion()), eau, SLOT(stop()));
        QObject::connect(terre, SIGNAL(explosion()), vent, SLOT(stop()));

        QObject::connect(feu, SIGNAL(explosion()), terre, SLOT(stop()));
        QObject::connect(feu, SIGNAL(explosion()), eau, SLOT(stop()));
        QObject::connect(feu, SIGNAL(explosion()), vent, SLOT(stop()));

        QObject::connect(eau, SIGNAL(explosion()), terre, SLOT(stop()));
        QObject::connect(eau, SIGNAL(explosion()), feu, SLOT(stop()));
        QObject::connect(eau, SIGNAL(explosion()), vent, SLOT(stop()));

        QObject::connect(vent, SIGNAL(explosion()), terre, SLOT(stop()));
        QObject::connect(vent, SIGNAL(explosion()), feu, SLOT(stop()));
        QObject::connect(vent, SIGNAL(explosion()), eau, SLOT(stop()));
    }


    for(int i=0; i<sorts->length(); i++)
        QObject::connect(sorts->value(i), SIGNAL(ajouterAffichable(Affichable*)), this, SLOT(ajoutAffichable(Affichable*)));

    timerSorts = new QTimer(this);
    timerSorts->setSingleShot(true);
    QObject::connect(timerSorts, SIGNAL(timeout()), this, SLOT(actualiserSorts()));
    isOnCast = false;


    QObject::connect(timerActualiser, SIGNAL(timeout()), this, SLOT(actualiser()));
    dureeActualisation = 5000 / stats.value(2);
    timerActualiser->start(dureeActualisation);

    // Timer Vie
    timerVie = new QTimer(this);
    QObject::connect(timerVie, SIGNAL(timeout()), this, SLOT(regenVie()));
    timerVie->setSingleShot(true);

    // Timer Mana
    timerMana = new QTimer(this);
    QObject::connect(timerMana, SIGNAL(timeout()), this, SLOT(regenMana()));
    timerMana->setSingleShot(true);

    timerStun = new QTimer(this);
    QObject::connect(timerStun, SIGNAL(timeout()), this, SLOT(finStun()));
    timerStun->setSingleShot(true);
    timerStun->start(2000);
}

void Personnage::newPet(int idAnimal)
{
    int typeAnimal;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../data/databases/animaux");
    db.open();
    QSqlQuery query(db);
    if(query.exec("SELECT * FROM animaux WHERE id=" + QString::number(idAnimal)))
    {
        while(query.next())
        {
            for(int i=0; i<19; i++)
                stats[i] += query.value(i+1).toInt();

            typeAnimal = query.value(20).toInt();
        }
    }
    db.close();
    vie = stats[0];
    mana = stats[1];


    animal = new Animal(nom, collision, typeAnimal,posX,posY);
    emit ajouterAffichable(animal);
    QObject::connect(this, SIGNAL(animalPosition(double,double,int)), animal, SLOT(setPosition(double,double,int)));

    gotAnimal = true;
    QVector<double> v(0);
    v.push_back(posX);
    v.push_back(posY);
    v.push_back(orientation);

    chemin = QVector<QVector<double>>(4+4*qMax(animal->getTailleX(), animal->getTailleY()), v);
    animal->setPosition(posX, posY, 0);

    if(type == 1)
        QObject::connect(sorts->value(2), SIGNAL(setInvisible(bool)), animal, SLOT(setInvisible(bool)));
}

void Personnage::finStun()
{
    stun = false;
    actualiser();
}

int Personnage::getTempsStun()
{
    return timerStun->remainingTime();
}

void Personnage::setInvisible(bool invisibleRecu)
{
    emit addToConsole(Qt::yellow, "Personnage (" + nom + ")", "setInvisible = " + QString::number(invisibleRecu), true, true);

    invisible = invisibleRecu;
    if(gotAnimal)
        animal->setInvisible(invisibleRecu);
    emit besoinRafraichir();
}

QString Personnage::getNom()
{
    return nom;
}

QVector<Sort*>* Personnage::getVecteurSorts()
{
    return sorts;
}

void Personnage::ajoutAffichable(Affichable *affichable)
{
    emit addToConsole(Qt::yellow, "Personnage (" + nom + ")", "ajoutAffichable", true, true);
    emit ajouterAffichable(affichable);
}

Personnage::~Personnage()
{
    delete player;
    delete equipement;

    delete sortFleche;
    delete sortDegatsArme;
    for(int i=0; i<sorts->size(); i++)
        delete sorts->takeAt(0);

    delete sorts;
    delete timerSorts;

    delete timerVie;
    delete timerMana;

    emit finish(animal);
}

void Personnage::deplacement(int xArrivee, int yArrivee)
{
    if(!estMort)
    {
        emit addToConsole(Qt::yellow, "Personnage (" + nom + ")", "Deplacement: dirX = " + QString::number(xArrivee) + "   / dirY = " + QString::number(yArrivee), true, false);

        xIncrement = xArrivee;
        yIncrement = yArrivee;
        action = 1;
        timerActualiser->start(dureeActualisation);
    }
}

void Personnage::setPos(double x, double y, int dir)
{
    if(!estMort)
    {
    emit addToConsole(Qt::yellow, "Personnage (" + nom + ")", "set posX = "+ QString::number(x) + "   / posY = " + QString::number(y) + "   / dir = " + QString::number(dir), true, false);
    if((x != posX) || (y != posY))
    {
        double aPosX = posX;
        double aPosY = posY;
        posX = x;
        posY = y;
        if(collision->collisionTerrain(this))
        {
            posX = aPosX;
            posY = aPosY;
            action = -1;
        }
        else
        {
            orientation = dir;

            if(gotAnimal)
            {
                animal->setPosition(chemin[0][0], chemin[0][1], chemin[0][2]);
                chemin.removeFirst();

                QVector<double> v(0);
                v.push_back(posX);
                v.push_back(posY);
                switch(orientation)
                {
                    case 0: // Haut
                    v.push_back(3);
                    break;

                    case 1: // Gauche
                    v.push_back(1);
                    break;

                    case 2: // Bas
                    v.push_back(0);
                    break;

                    case 3: // Droite
                    v.push_back(2);
                    break;
                }
                if((qAbs(posX-aPosX) + qAbs(posY-aPosY)) >= 0.5)
                {
                    chemin = QVector<QVector<double>>(4+4*qMax(animal->getTailleX(), animal->getTailleY()), v);
                    animal->setPosition(posX, posY, 0);
                }
                else
                    chemin.push_back(v);
            }


            actionSprite = 1;
            if(etape >= 8)
                etape = 0;
            else
                etape+=0.5;
        }
    }
    }
}

void Personnage::changerArme()
{
    if(!estMort)
    {
    emit addToConsole(Qt::yellow, "Personnage (" + nom + ")", "changerArme", true, false);

    equipement->echangerArmes();
    arme = equipement->getFirstArme();
    }
}

void Personnage::attaquer(int seedRecu)
{
    if(!estMort)
    {
    emit addToConsole(Qt::yellow, "Personnage (" + nom + ")", "Attaquer", true, false);

    setInvisible(false);

    seed = seedRecu;
    action = 2;
    etape = 0;
    dureeActualisation = 500000 / stats.value(2) / arme->getVitesse();

    if((arme->getType() == 0) || (arme->getType() == 1) || (arme->getType() == 2)) // Si l'arme est un arc
        dureeActualisation /= 1.5;

    timerActualiser->start(dureeActualisation);
    }
}


void Personnage::actualiser()
{
    qDebug() << "perso Actualiser";
    emit addToConsole(Qt::yellow, "Personnage (" + nom + ")", "actualiser", true, false);

    if(!estMort)
    {
        if(stun)
        {
            action = -1;
            emit besoinRafraichir();
            timerActualiser->start(100);
        }

        switch (action)
        {
            case -1: // Inactif
            actionSprite = 1;
            etape = 0;
            emit besoinRafraichir();
            break;



            case 0: // Cast Sort
            actionSprite = 0;
            if(etape >= 6)
            {
                action = -1;
                sorts->value(sortEnTrainDeCast)->finCast();
                actualiserSorts();
                isOnCast = false;
            }
            else
            {
                etape++;
            }
            emit besoinRafraichir();
            timerActualiser->start(dureeActualisation);
            break;



            case 1: // Deplacement
            dureeActualisation = 5000 / stats.value(2);
            if(isOnCast)
            {
                mana += sorts->value(sortEnTrainDeCast)->getCoutMana() / 2;
                sorts->value(sortEnTrainDeCast)->end();
                emit actualiserInterface();
                isOnCast = false;
            }
            actionSprite = 1;
            if((xIncrement != 0) || (yIncrement != 0)) // Si le personnage se déplace
            {
                int orient = -1;
                    // Et on redéfini l'orientation du personnage
                    if(xIncrement == 1)
                        orient = 3;
                    else if(xIncrement == -1)
                        orient = 1;

                    if(yIncrement == 1)
                        orient = 2;
                    else if(yIncrement == -1)
                        orient = 0;

                double x = posX+xIncrement/8.0;
                double y = posY+yIncrement/8.0;

                emit signalSetPos(nom,x,y,orient);

                player->play();
            }
            else
            {
                action = -1;
            }
            emit besoinRafraichir();
            timerActualiser->start(dureeActualisation/2);
            break;



            case 2: // Attaque avec arme
            if(isOnCast)
            {
                mana += sorts->value(sortEnTrainDeCast)->getCoutMana() / 2;
                sorts->value(sortEnTrainDeCast)->end();
                emit actualiserInterface();
                isOnCast = false;
            }
            actionSprite = 2;
            if(etape >= arme->getEtapeMax()-1) // Si on a fini l'animation d'attaque
            {
                action = -1;
                int type = arme->getType();
                if((type == 0) || (type == 1) || (type == 2)) // Si l'arme est un arc
                {
                    sortFleche->cast(seed,posX,posY);
                    sortFleche->finCast();
                }
                else if((type == 3) || (type == 4) || (type == 5) || (type == 6))
                {
                    sortDegatsArme->cast(seed,posX,posY);
                    sortDegatsArme->finCast();
                }
            }
            else
            {
                etape++;
            }

            emit besoinRafraichir();
            timerActualiser->start(dureeActualisation);
            break;
        }
    }
    else
    {
        if(etape < 5)
        {
            etape++;
            emit besoinRafraichir();
            timerActualiser->start(120);
        }
    }
}

void Personnage::castSort(int seedRecu, int i, double x, double y)
{
    if(!estMort)
    {
    emit addToConsole(Qt::yellow, "Personnage (" + nom + ")", "cast sort = " + QString(i) + "   / posX = "+ QString::number(x) + "   / posY = " + QString::number(y), true, false);

    if(sorts->length() > i)
    {
        bool valide = false;
        double sortX, sortY;
        Sort *sort = sorts->value(i);
        if(sort->isAvailable())
        {
            if(sort->isCiblable())
            {
                int distance = sqrt(qPow(posX - x, 2) + qPow(posY - y, 2));
                if(sort->isInRange(distance))
                {
                    sortX = x;
                    sortY = y;
                    valide = true;
                }
            }
            else
            {
                sortX = posX;
                sortY = posY;
                valide = true;
            }
        }
        else
            emit addToConsole(Qt::yellow, "Personnage (" + nom + ")", "sort " + QString::number(i) + " not available  / Cd = " + QString::number(sort->getCooldownRemaining()) + "   / Cast: = " + QString::number(sort->isCasting()), true, false);

        if(valide)
        {
            if(isOnCast)
            {
                mana += sorts->value(sortEnTrainDeCast)->getCoutMana() / 2;
                sorts->value(sortEnTrainDeCast)->end();
                emit actualiserInterface();
                isOnCast = false;
            }
            if(mana >= sort->getCoutMana())
            {
                setInvisible(false);

                mana -= sort->getCoutMana();
                timerMana->start(1000);

                isOnCast = true;
                sort->cast(seedRecu, sortX, sortY);
                emit actualiserInterface();
                sortEnTrainDeCast = i;
                action = 0;
                etape = 0;
                if(sort->getCast() > 0)
                {
                    dureeActualisation = sort->getCast() * 100 / stats.value(2) / 8;

                    if(dureeActualisation  == 0)
                    {
                        action = -1;
                        sorts->value(sortEnTrainDeCast)->finCast();
                        actualiserSorts();
                        isOnCast = false;
                    }
                    else
                        timerActualiser->start(dureeActualisation);
                }
                else
                {
                    action = -1;
                    sort->finCast();
                    actualiserSorts();
                }
            }
        }
    }
    }
}

void Personnage::actualiserSorts()
{
    emit actualiserInterface();
    if(!timerSorts->isActive())
    {
        for(int i=0; i<sorts->length(); i++)
        {
            if(sorts->value(i)->isOnCd())
            {
                timerSorts->start(100);
                return;
            }
        }
    }
}

void Personnage::setStun(bool stunRecu)
{
    if(!estMort)
    {
    emit addToConsole(Qt::yellow, "Personnage (" + nom + ")", "setStun = " + QString(stunRecu), true, false);

    stun = stunRecu;
    if(stun)
        timerStun->start(2000);
    }
}

void Personnage::subirDegats(QVector<int> vecteurDegats)
{
    if(!estMort)
    {
        int degats = 0;
        invisible = false;
        if(gotAnimal)
            animal->setInvisible(false);

        for(int i=0; i<4; i++)
            degats += double(vecteurDegats[i] * ((100 - stats[10+i] - stats[14])/100.0));

        if(vecteurDegats[4] == 1)
            emit signalSetVie(nom,qMax(0,vie-degats),true);
        else
            emit signalSetVie(nom,qMax(0,vie-degats),false);
    }
}

void Personnage::setVie(int vieRecu, bool stunRecu)
{
    if(!estMort)
    {
        emit addToConsole(Qt::yellow, "Personnage (" + nom + ")", "set vie = " + QString(vieRecu) + "   / setStun = "+ QString::number(stunRecu), true, false);

        vie = vieRecu;
        if(!estVivant())
        {
            timerVie->stop();
            timerMana->stop();
            vie = 0;
            estMort = true;
            action= -1;
            etape = 0;
            mort++;
            timerMort->start(5000);
            emit ajouterAnnonce(nom + " a été tué !");
            actualiser();
        }
        else
        {
            if(stunRecu)
            {
                stun = stunRecu;
                timerStun->start(2000);
            }
            timerVie->start();
        }

        emit actualiserInterface();
    }
}

void Personnage::revivre()
{
    if(mort < 3)
    {
        emit addToConsole(Qt::yellow, "Personnage (" + nom + ")", "revivre   / morts restantes = " + QString::number(mort), true, true);

        estMort = false;
        action = -1;
        etape = 0;

        vie = stats[0];
        mana = stats[1];

        posX = 0;
        posY = 0;
        qsrand(QDateTime::currentDateTime ().toTime_t ());
        do
        {
            setPos(qrand() % map->getLargeur(), qrand() % map->getHauteur(), 0);
        }while(posX == 0);
        emit signalSetPos(nom,posX,posY,orientation);

        if(gotAnimal)
        {
            QVector<double> v(0);
            v.push_back(posX);
            v.push_back(posY);
            v.push_back(orientation);

            chemin = QVector<QVector<double>>(4+4*qMax(animal->getTailleX(), animal->getTailleY()), v);
            animal->setPosition(posX, posY, 0);
        }

        actualiser();
        emit actualiserInterface();
    }
    else
    {
        emit supprimerPerso(nom);
        emit addToConsole(Qt::yellow, "Personnage (" + nom + ")", "perdu", true, true);
    }
}

void Personnage::ajouterVie(int vieAjoutee)
{
    if(!estMort)
    {
    vie += vieAjoutee;
    if(vie > stats[0])
        vie = stats[0];

   emit actualiserInterface();
    }
}

void Personnage::regenVie()
{
    if(!estMort)
    {
    if(vie < stats[0])
        vie = qMin(vie + stats[3], stats[0]);

    if(vie < stats[0])
        timerVie->start(1000);

    emit actualiserInterface();
    }
}

void Personnage::regenMana()
{
    if(!estMort)
    {
    if(mana < stats[1])
        mana = qMin(mana + stats[4], stats[1]);

    if(mana < stats[1])
        timerMana->start(1000);

    emit actualiserInterface();
    }
}


void Personnage::findSave(int numero)
{
    stats = QVector<int>(0,0);
    // Ouverture de la base de données
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../data/databases/personnages");
    db.open();
    QSqlQuery query(db);
    if(query.exec("SELECT * FROM persos WHERE id=" + QString::number(numero)))
    {
        while(query.next())
        {
            for(int i=0; i<18; i++)
                stats.push_back(query.value(i+1).toInt());

            stats.push_back(0);

            QVector<int> vecteurArmes(0,0);
            for(int i=0; i<3; i++)
            {
                if(query.value(i+19).toInt() != 0)
                    vecteurArmes.push_back(query.value(i+19).toInt());
            }

            classe = query.value(23).toString();
            descriptionSorts[0] = "Changer d'arme";
            descriptionSorts[1] = "Change d'arme instantanément d'arme";

            for(int i=0; i<10; i++)
                descriptionSorts[i+2] = query.value(24+i).toString();

            equipement = new Equipement(vecteurArmes);
            arme = equipement->getFirstArme();
            numeroSprite = query.value(22).toInt();
            buildSprites();
        }
    }
    db.close();

    vie = stats[0];
    mana = stats[1];

    posX = 0;
    posY = 0;
    qsrand(QTime::currentTime().msec());
    do
    {
        setPos(qrand() % map->getLargeur(), qrand() % map->getHauteur(), 0);
    }while(posX == 0);
    emit signalSetPos(nom,posX,posY,orientation);

}


void Personnage::buildSprites()
{
    for(int z=0; z<3; z++)
    {
        QImage imagePerso = QImage("../data/images/sprites/" + QString::number(numeroSprite) + "_" + QString::number(z) + ".png").scaled(832, 1344);
        for(int y=0; y<4; y++)
        {
            for(int x=0; x<13; x++)
            {
                sprites[z][0][y][x] = imagePerso.copy(1+x*64, 1+(y+0)*64, 64, 64);
                sprites[z][1][y][x] = imagePerso.copy(1+x*64, 1+(y+8)*64, 64, 64);
                sprites[z][2][y][x] = imagePerso.copy(1+x*64, 1+(y+16)*64, 64, 64);
            }
        }
    }

        QImage imagePerso = QImage("../data/images/sprites/" + QString::number(numeroSprite) + "_3.png").scaled(832, 1344);
        for(int y=0; y<4; y++)
        {
            for(int x=0; x<13; x++)
            {
                sprites[3][0][y][x] = imagePerso.copy(1+x*64, 1+(y+0)*64, 64, 64);
                sprites[3][1][y][x] = imagePerso.copy(1+x*64, 1+(y+8)*64, 64, 64);
                sprites[3][2][y][x] = imagePerso.copy(1+x*64, 1+(y+4)*64, 64, 64);
            }
        }

    for(int z=4; z<7; z++)
    {
        QImage imagePerso = QImage("../data/images/sprites/" + QString::number(numeroSprite) + "_" + QString::number(z) + ".png").scaled(832, 1344);
        for(int y=0; y<4; y++)
        {
            for(int x=0; x<13; x++)
            {
                sprites[z][0][y][x] = imagePerso.copy(1+x*64, 1+(y+0)*64, 64, 64);
                sprites[z][1][y][x] = imagePerso.copy(1+x*64, 1+(y+8)*64, 64, 64);
                sprites[z][2][y][x] = imagePerso.copy(1+x*64, 1+(y+12)*64, 64, 64);
            }
        }
    }

    QImage imagePersoMort = QImage("../data/images/sprites/" + QString::number(numeroSprite) + "_0.png").scaled(832, 1344);
    imageMort= QVector<QImage>(0);

    for(int x=0; x<6; x++)
      imageMort.push_back(imagePersoMort.copy(1+x*64, 1+(20+0)*64, 64, 64));

}


QImage* Personnage::getSprite()
{
    if(estMort)
        return &imageMort[int(etape)];
    else
        return &sprites[arme->getType()][actionSprite][orientation][int(etape)];
}

double Personnage::getPosXAffichage()
{
    return posX-0.166;
}

double Personnage::getPosYAffichage()
{
    return posY-0.166;
}

QRectF Personnage::getHitbox()
{
    return QRectF(posX +0.15, posY+0.28, 0.6, 0.80);
}

void Personnage::envoyerMessage(QString message)
{
    emit envoyer(message);
}
