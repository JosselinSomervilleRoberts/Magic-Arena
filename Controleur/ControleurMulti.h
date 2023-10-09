#ifndef CONTROLEURMULTI_H
#define CONTROLEURMULTI_H

#include "Controleur/Controleur.h"
#include "Communication/Communication.h"

class ControleurMulti : public Controleur
{
    Q_OBJECT

public:
    ControleurMulti();
    ~ControleurMulti();

public slots:
    void chargerJeu(int indexMapRecu, Communication *com);
    void lancerPartie();

private:
    Communication *communication;
};

#endif // CONTROLEURMULTI_H
