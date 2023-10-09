#ifndef AFFICHABLE_H
#define AFFICHABLE_H

#include <QtWidgets>

class Affichable : public QObject
{
    Q_OBJECT




public:
    Affichable();
    ~Affichable();

    bool operator==(const int entier) const
    {
        if(exist == entier)
            return true;

        return false;
    }

    double getPosX();
    double getPosY();
    double getTailleX();
    double getTailleY(); 
    int getIncrementX();
    int getIncrementY();

    virtual void buildSprites() = 0;
    virtual QImage* getSprite() = 0;
    virtual double getPosXAffichage() = 0;
    virtual double getPosYAffichage() = 0;
    virtual QRectF getHitbox() = 0;


signals:
    void besoinRafraichir();
    void finish(Affichable *);
    // Debug
    void addToConsole(QColor couleur, QString source, QString message, bool newLine, bool important);


protected:
    int exist;
    double posX, posY, tailleX, tailleY;
    int xIncrement, yIncrement;
    QRectF hitbox;
    QTimer *timerActualiser;
};

#endif // AFFICHABLE_H
