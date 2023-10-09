#include "Map/Collision.h"

Collision::Collision(QVector<Affichable*> *vecteurAffichablesRecu, Map *mapRecu) : QObject()
{
    map = mapRecu;
    vecteurAffichables = vecteurAffichablesRecu;
    obstacles = map->getObstacles();
}


bool Collision::collisionTerrain(Affichable *affichable)
{
    if((affichable != nullptr) && (*affichable == 1))
    {
        QRectF rect = affichable->getHitbox();
        for(int i=0; i<obstacles->length(); i++)
        {
            if(obstacles->value(i).intersects(rect))
            {
                emit addToConsole(QColor(180,110,75), "Collision", "collision terrain", true, true);
                return true;
            }
        }
        return false;
    }
    else
    {

        emit addToConsole(QColor(180,110,75), "Collision", "affichable alredy deleted", true, true);
        vecteurAffichables->removeOne(affichable);
        emit addToConsole(QColor(180,110,75), "Collision", "affichable remove from vecteur", true, true);
        return false;
    }
}


bool Collision::collisionAffichable(Affichable *affichable)
{
    if((affichable != nullptr) && (*affichable == 1))
    {
        int index = vecteurAffichables->indexOf(affichable, 0);
        bool collision = false;
        QRectF rectangle = vecteurAffichables->value(index)->getHitbox();

        for(int i=0; i<vecteurAffichables->size(); i++)
        {
            if(i != index)
            {
                if(rectangle.intersects(vecteurAffichables->value(i)->getHitbox()))
                {
                    collision = true;
                    emit addToConsole(QColor(180,110,75), "Collision", "collision affichables", true, true);
                    emit collisionDeAffichables(vecteurAffichables->value(index), vecteurAffichables->value(i));
                }
            }
        }

        return collision;
    }
    else
    {
        emit addToConsole(QColor(180,110,75), "Collision", "affichable alredy deleted", true, true);
        vecteurAffichables->removeOne(affichable);
        emit addToConsole(QColor(180,110,75), "Collision", "affichable remove from vecteur", true, true);
        return false;
    }
}
