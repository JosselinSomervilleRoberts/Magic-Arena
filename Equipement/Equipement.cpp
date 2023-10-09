#include "Equipement/Equipement.h"

Equipement::Equipement(QVector<int> vecteurArmesRecu) : QObject()
{
    vecteurEquipables = new QVector<Equipable*>();
    autoFind(vecteurArmesRecu);
}

Equipement::~Equipement()
{
    //save();

    for(int i=0; i<vecteurEquipables->length(); i++)
        delete vecteurEquipables->takeAt(0);

    delete vecteurEquipables;
}

Arme* Equipement::getFirstArme()
{
    for(int i=0; i<vecteurEquipables->length(); i++)
    {
        if(Arme* arme = dynamic_cast<Arme*>(vecteurEquipables->value(i)))
            return arme;
    }
    return 0;
}

void Equipement::autoFind(QVector<int> vecteurArmesRecu)
{
    for(int i=0; i<vecteurArmesRecu.length(); i++)
    {
        Arme *arme = new Arme(vecteurArmesRecu[i]);
        vecteurEquipables->push_back(arme);
    }
}

/*void Equipement::save()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../data/databases/josselin/save");
    db.open();

    QSqlQuery query(db);

    for(int i=0; i<vecteurEquipables->length(); i++)
        query.exec("UPDATE equipement SET idObjet=" + QString::number(vecteurEquipables->value(i)->getId()) + " WHERE id=" + QString::number(i+1));
}*/

void Equipement::echangerArmes()
{
    QVector<int> vecteurArmes;
    for(int i=0; i<vecteurEquipables->length(); i++)
    {
        if(Arme* arme = dynamic_cast<Arme*>(vecteurEquipables->value(i)))
            vecteurArmes.push_back(i);
    }

    if(vecteurArmes.length() >= 2)
    {
        Equipable *armeProvisoire = vecteurEquipables->value(0);
        for(int i=1; i<vecteurArmes.length(); i++)
            vecteurEquipables->replace(vecteurArmes[i-1], vecteurEquipables->value(vecteurArmes[i]));

        vecteurEquipables->replace(vecteurArmes.last(), armeProvisoire);
    }
}

/*QVector<int> Equipement::getStats()
{
    calculStats();
    return stats;
}

void Equipement::calculStats()
{
    for(int i=0; i<stats.length(); i++)
        stats[i] = 0;

    for(int i=0; i<vecteurEquipables->length(); i++)
    {
        QVector<int> vecteurProvisoire = vecteurEquipables->value(i)->getStats();

        for(int index=0; index<vecteurProvisoire.length(); index++)
            stats[i] += vecteurProvisoire[index];
    }
}

void Equipement::recevoirEquipable(Equipable* equipableRecu)
{
    vecteurEquipables->push_back(equipableRecu);
}

Equipable* Equipement::getEquipable(int index)
{
    return vecteurEquipables->value(index);
}

void Equipement::supprimerEquipable(int index)
{
    vecteurEquipables->removeAt(index);
}*/
