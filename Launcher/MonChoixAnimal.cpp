#include "MonChoixAnimal.h"

MonChoixAnimal::MonChoixAnimal(QWidget *parent) : QWidget(parent)
{
    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height();
    int width = rec.width();
    int tailleCase = qMin(width / 40, int(height / 21));
    int nbParLignes = 12;


    layoutPrincipal = new QGridLayout(this);
    layoutPrincipal->setContentsMargins(0,0,0,0);
    layoutPrincipal->setSpacing(0);

    int nbAnimaux = 0;

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../data/databases/animaux");
    db.open();
    QSqlQuery query(db);

    group = new QButtonGroup(this);
    group->setExclusive(true);
    QObject::connect(group, SIGNAL(buttonPressed(int)), this, SLOT(buttonChanged(int)));

    if(query.exec("SELECT * FROM animaux"))
    {
        while(query.next())
        {
            if(nbAnimaux % nbParLignes == 0)
                boutons.push_back(QVector<QPushButton*>(0));

            QPushButton *bouton = new QPushButton(this);
            bouton->setStyleSheet("width: " + QString::number(tailleCase) + "px; height: " + QString::number(tailleCase) + "px; border-image: url(../data/images/launcher/animaux/" + query.value(20).toString() + ".png) 0 0 0 0 stretch stretch;");
            bouton->setCheckable(true);
            boutons[nbAnimaux/nbParLignes].push_back(bouton);

            layoutPrincipal->addWidget(bouton, 1+6*(nbAnimaux/nbParLignes), 1+6*(nbAnimaux-(nbAnimaux/nbParLignes)*nbParLignes), 5, 5);
            nbAnimaux++;
            group->addButton(bouton, nbAnimaux);
        }
        boutons.first().first()->setChecked(true);
    }
    db.close();

    int nbAnimaux2 = 0;
    db.setDatabaseName("../data/databases/save");
    db.open();
    QSqlQuery query2(db);
    if(query2.exec("SELECT * FROM animaux"))
    {
        while(query2.next())
        {
            nbAnimaux2++;
            if(query2.value(1).toInt() == 0)
            {
                group->button(nbAnimaux2)->setStyleSheet("width: " + QString::number(tailleCase) + "px; height: " + QString::number(tailleCase) + "px; border-image: url(../data/images/launcher/lock.png) 0 0 0 0 stretch stretch;");
                group->button(nbAnimaux2)->setEnabled(false);
            }
        }
    }
    db.close();

    QLabel *label = new QLabel(this);
    QPixmap pixmap(tailleCase * 14, tailleCase * 10.5);
    pixmap.fill(QColor(80,80,80,240));
    label->setPixmap(pixmap);
    label->lower();
    layoutPrincipal->addWidget(label, 0, 0, 1 + (nbAnimaux/nbParLignes +1) * 6,1 + qMin(nbParLignes, nbAnimaux) * 6);

    //setFixedSize(tailleCase*(qMin(nbParLignes, nbAnimaux) * 6/5) + 1/5 * tailleCase, tailleCase*((nbAnimaux/nbParLignes +1) * 6/5) + 1/5 * tailleCase);
    setFixedSize(tailleCase * 14, tailleCase * 10.5);
    setStyleSheet("QWidget {background-color: transparent;}");
}

int MonChoixAnimal::getId()
{
    return group->checkedId();
}

void MonChoixAnimal::buttonChanged(int boutonRecu)
{
    emit animalChanged(boutonRecu);
}
