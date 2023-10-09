#include "Equipable.h"

Equipable::Equipable(int idRecu) : QObject(), id(idRecu), stats(18, 0)
{
    findFromID();
}

int Equipable::getId()
{
    return id;
}

QString Equipable::getNom()
{
    return nom;
}

int Equipable::getNiveau()
{
    return niveau;
}

int Equipable::getImage()
{
    return image;
}

int Equipable::getType()
{
    return type;
}

void Equipable::findFromID()
{
    // Ouverture de la base de données
    QSqlDatabase db;
    db.setDatabaseName("../data/databases/equipement");
    db.open();

    QSqlQuery query(db);
    if(query.exec("SELECT * FROM stats WHERE id=" + QString::number(id)))
    {
        while(query.next())
        {
            for(int i=0; i<18; i++)
                stats[i] = query.value(i+1).toInt();

            niveau = query.value(19).toInt();
            image = query.value(20).toInt();
            type = query.value(21).toInt();
            nom = query.value(22).toString();
        }
    }
    db.close();
}

void Equipable::setStats(QVector<int> statsRecu)
{
    stats = statsRecu;
}

QVector<int> Equipable::getStats()
{
    return stats;
}
