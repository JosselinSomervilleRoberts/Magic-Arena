#ifndef MONSTRE_H
#define MONSTRE_H

#include "Vivants/Personnage.h"


class Monstre : public Personnage
{
    Q_OBJECT

public:
    Monstre(bool persoPrincipalRecu, int typeRecu, QString nomRecu, Map *mapRecu, Collision *collisionRecu);
};

#endif // MONSTRE_H
