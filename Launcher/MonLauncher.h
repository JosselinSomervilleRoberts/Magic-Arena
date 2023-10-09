#ifndef MONLAUNCHER_H
#define MONLAUNCHER_H

#include <QtWidgets>
#include <QtSql>

#include "Communication/Communication.h"
#include "ImageSlider.h"
#include "Controleur/ControleurMulti.h"
#include "MonChoixAnimal.h"

class MonLauncher : public QWidget
{
    Q_OBJECT

public:
    MonLauncher(QApplication *app);
    ~MonLauncher();

public slots:
    void reduire();

    void launch(bool);
    void selectPerso(int);
    void newParticipant(QString,bool);
    void deleteParticipant(QString);
    void setPret();

    void start(int);
    void chooseMap();
    void setMap(int);

    void switchFenetres();
    void animalChanged(int);

private:
    int idAnimal;
    bool animalShown;
    MonChoixAnimal *widgetAnimal;

    ImageSlider *slider;
    int width, height, tailleCase, dpi;

    QLabel *texteConnexion;
    QLabel *gifConnexion;
    QMovie *gif;

    QLabel *labelFond;
    QPixmap pixmapFond;
    QGridLayout *layoutPrincipal;
    QGridLayout *layoutPerso;
    QWidget *widgetPerso;

    Communication *com;
    QString nom;
    bool pret;
    QSqlDatabase db;

    QVector<QLabel*> labelsPerso;
    QVector<QLabel*> participants;

    QPushButton *boutonPret;
    QPushButton *boutonSwitch;
    QButtonGroup *group;

    ControleurMulti fenetre;
};

#endif // MONLAUNCHER_H
