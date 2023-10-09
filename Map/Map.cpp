#include "Map.h"

Map::Map() : QObject(), obstacles(0, QRectF(0,0,0,0))
{
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
}


void Map::setMap(int numeroRecu)
{
    if(numeroRecu == 10)
        playlist->addMedia(QUrl::fromLocalFile("../data/musiques/background/10.mp3"));
    else
        playlist->addMedia(QUrl::fromLocalFile("../data/musiques/background/Bataille.mp3"));

    player->setPlaylist(playlist);
    player->setVolume(50);
    player->play();

    numero = numeroRecu;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../data/databases/maps");
    db.open();

    QSqlQuery query(db);

    hauteur = 0;
    if(query.exec("SELECT * FROM map_" + QString::number(numero)))
        while(query.next())
           hauteur++;

    largeur = query.record().count() - 1;

    QVector<QVector<int>> tableauProvisoire(largeur, QVector<int>(hauteur, 0));
    map = tableauProvisoire;

    obstacles.push_back(QRectF(0,0,0.01,hauteur));
    obstacles.push_back(QRectF(largeur-0.01,0,0.01,hauteur));
    obstacles.push_back(QRectF(0,0,largeur,0.01));
    obstacles.push_back(QRectF(0,hauteur-0.01,largeur,0.01));


    if(query.exec("SELECT * FROM map_" + QString::number(numero) + " ORDER BY id ASC"))
    {
        int y = 0;
        while(query.next())
        {
            for(int x=0; x<largeur; x++)
            {
                map[x][y] = query.value(x+1).toInt();
                switch(map[x][y])
                {
                    case 1:
                    obstacles.push_back(QRectF(x,y,1,0.8));
                    break;

                    case 10:
                    obstacles.push_back(QRectF(x,y,0.01,1));
                    obstacles.push_back(QRectF(x+0.99,y,0.01,1));
                    obstacles.push_back(QRectF(x,y,1,0.01));
                    break;

                    case 11:
                    obstacles.push_back(QRectF(x,y,0.01,1));
                    obstacles.push_back(QRectF(x+0.99,y,0.01,1));
                    obstacles.push_back(QRectF(x,y+0.99,1,0.01));
                    break;

                    case 12:
                    obstacles.push_back(QRectF(x+0.99,y,0.01,1));
                    obstacles.push_back(QRectF(x,y,1,0.01));
                    obstacles.push_back(QRectF(x,y+0.99,1,0.01));
                    break;

                    case 13:
                    obstacles.push_back(QRectF(x,y,0.01,1));
                    obstacles.push_back(QRectF(x,y,1,0.01));
                    obstacles.push_back(QRectF(x,y+0.99,1,0.01));
                    break;

                    case 14:
                    obstacles.push_back(QRectF(x+0.99,y,0.01,1));
                    obstacles.push_back(QRectF(x,y,1,0.01));
                    break;

                    case 15:
                    obstacles.push_back(QRectF(x,y,0.01,1));
                    obstacles.push_back(QRectF(x,y,1,0.01));
                    break;

                    case 16:
                    obstacles.push_back(QRectF(x+0.99,y,0.01,1));
                    obstacles.push_back(QRectF(x,y+0.99,1,0.01));
                    break;

                    case 17:
                    obstacles.push_back(QRectF(x,y,0.01,1));
                    obstacles.push_back(QRectF(x,y+0.99,1,0.01));
                    break;

                    case 18:
                    obstacles.push_back(QRectF(x,y,0.01,1));
                    obstacles.push_back(QRectF(x+0.99,y,0.01,1));
                    break;

                    case 19:
                    obstacles.push_back(QRectF(x,y,1,0.01));
                    obstacles.push_back(QRectF(x,y+0.99,1,0.01));
                    break;

                    case 20:
                    obstacles.push_back(QRectF(x+0.99,y+0.09,0.01,0.82));
                    break;

                    case 21:
                    obstacles.push_back(QRectF(x,y+0.09,0.01,0.82));
                    break;

                    case 22:
                    obstacles.push_back(QRectF(x+0.09,y,0.82,0.01));
                    break;

                    case 23:
                    obstacles.push_back(QRectF(x+0.09,y+0.99,0.82,0.01));
                    break;
                }
            }
            y++;
        }
    }
    db.close();
}

void Map::ajouterObstacles(QVector<QRectF> vecteur)
{
    for(int i=0; i<vecteur.length(); i++)
        obstacles.push_back(vecteur[i]);
}

void Map::retirerObstacles(QVector<QRectF> vecteur)
{
    for(int i=0; i<vecteur.length(); i++)
        obstacles.removeOne(vecteur[i]);
}

Map::~Map()
{
    delete player;
    delete playlist;
}

void Map::setVolume(int volumeRecu)
{
    player->setVolume(volumeRecu);
}
