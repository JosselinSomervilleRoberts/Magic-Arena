#ifndef VIVANT_H
#define VIVANT_H

#include "Affichable.h"


class Vivant : public Affichable
{
    Q_OBJECT


public:
    Vivant();
    bool estVivant();
    int getAction();
    int getOrientation();
    double getEtape();

    int getVie() { return vie; }
    int getMana() { return mana; }


public slots:
    void stopAttaque();
    void deplacer(int, int, int);
    void stopDeplacementX();
    void stopDeplacementY();


signals:
    void estMort();
    void actualiserInterface();


protected:
    QVector<int> stats;
    int niveau, vie, mana, xp;
    int orientation, etapeMax, vitesse, action, actionSprite; // Déplacement
    double etape;
};

#endif // VIVANT_H
