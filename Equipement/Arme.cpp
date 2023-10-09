#include "Arme.h"

Arme::Arme(int id) : Equipable(id), degats(8, 0)
{
    getArme();
    qsrand(QDateTime::currentDateTime ().toTime_t ());
}

void Arme::getArme()
{
    // Ouverture de la base de données
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../data/databases/equipement");
    db.open();

    QSqlQuery query(db);
    if(query.exec("SELECT * FROM arme WHERE id=" + QString::number(id)))
    {
        while(query.next())
        {
            icone = query.value(0).toInt();

            for(int i=0; i<8; i++)
                degats[i] = query.value(i+2).toInt();

            tauxStun = query.value(10).toInt();
            tauxCrit = query.value(11).toInt();
            degatsCrit = query.value(12).toInt();
            vitesse = query.value(13).toInt();
            type = query.value(14).toInt();
            portee = query.value(15).toInt();

            switch(type)
            {
                case 0:
                etapeMax = 13;
                break;

                case 1:
                etapeMax = 13;
                break;

                case 2:
                etapeMax = 13;
                break;

                case 3:
                etapeMax = 8;
                break;

                case 4:
                etapeMax = 6;
                break;

                case 5:
                etapeMax = 6;
                break;

                case 6:
                etapeMax = 6;
                break;
            }
        }
    }
    db.close();
}
