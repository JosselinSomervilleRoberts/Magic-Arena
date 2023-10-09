#ifndef MONCHOIXANIMAL_H
#define MONCHOIXANIMAL_H

#include <QtWidgets>
#include <QtSql>

class MonChoixAnimal : public QWidget
{
    Q_OBJECT

public:
    explicit MonChoixAnimal(QWidget *parent = 0);

signals:
    void animalChanged(int);

public slots:
    int getId();
    void buttonChanged(int);

protected:
    QButtonGroup *group;
    QVector<QVector<QPushButton*>> boutons;

    QGridLayout *layoutPrincipal;
};

#endif // MONCHOIXANIMAL_H
