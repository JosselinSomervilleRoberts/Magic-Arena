#ifndef ARME_H
#define ARME_H

#include <QWidget>
#include "Equipable.h"

class Arme : public Equipable
{    
    Q_OBJECT

public:
    Arme(int id);
    void getArme();

    QVector<int> getDegats() { return degats; }
    int getTauxStun() { return tauxStun; }
    int getTauxCrit() { return tauxCrit; }
    int getDegatsCrit() { return degatsCrit; }

    int getEtapeMax() { return etapeMax; }
    int getType() { return type; }
    int getPortee() { return portee; }
    int getVitesse() { return vitesse; }
    int getIcone() { return icone; }

protected:
    int icone, tauxStun, tauxCrit, degatsCrit, type, portee, vitesse, etapeMax;
    QVector<int> degats;
};

#endif // ARME_H
