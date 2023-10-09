#ifndef PARAMETRES_H
#define PARAMETRES_H

#include <QtWidgets>

class Parametres : public QWidget
{
    Q_OBJECT

public:
    Parametres(QVector<int> parametresRecu, QWidget *parent = 0);
    ~Parametres();

public slots:
    void finish();
    void deleteThis();

protected :
    void keyPressEvent (QKeyEvent *event); // Détecte l'appui d'une touche clavier
    void mousePressEvent(QMouseEvent* event);

signals:
    void newKeys(QVector<int>);
    void deleteParametres();

protected:
    QVector<int> parametres;
    QVector<QPushButton*> boutons;
    QButtonGroup *group;

    int raccourcis[52];
    QString textes[52];

    QGridLayout *layoutPrincipal;
    QLabel *fond;
    QLabel *titre;
    QPushButton *valider;
};

#endif // PARAMETRES_H
