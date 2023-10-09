#include "EffetsCollision.h"

EffetsCollision::EffetsCollision() : QObject()
{}

void EffetsCollision::checkEffetsCollision(Affichable * toucheur, Affichable * touche)
{
    if((*toucheur == 1) && (*touche == 1))
        appliquerEffets(toucheur, touche);
}

void EffetsCollision::appliquerEffets(Affichable *affichable1, Affichable *affichable2)
{
    if(Personnage* perso = dynamic_cast<Personnage*>(affichable1))
    {
        if(perso->estVivant())
        {
            if(Boule* boule = dynamic_cast<Boule*>(affichable2))
            {
                if(perso->getNom() != boule->getLanceur())
                {
                    if(perso->isPersoPrincipal())
                        perso->subirDegats(boule->getDegats());
                }
            }

            if(Projectile* projectile = dynamic_cast<Projectile*>(affichable2))
            {
                if(perso->getNom() != projectile->getLanceur())
                {
                    if(perso->isPersoPrincipal())
                    {
                        projectile->calculDegats();
                        perso->subirDegats(projectile->getDegats());
                    }
                    projectile->collisionDetectee();
                }
            }
        }
    }
    else
    {
        if(Personnage* perso = dynamic_cast<Personnage*>(affichable2))
        {
            if(perso->estVivant())
                appliquerEffets(affichable2, affichable1);
        }
    }
}
