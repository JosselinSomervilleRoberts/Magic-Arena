#ifndef EQUIPABLE_H
#define EQUIPABLE_H

#include <QtSql>
#include <QWidget>

class Equipable : public QObject
{
    Q_OBJECT

public:
    Equipable(int idRecu);
    void findFromID();

    void setStats(QVector<int> statsRecu);
    QVector<int> getStats();
    int getId();
    QString getNom();
    int getNiveau();
    int getImage();
    int getType();


protected:
    QVector<int> stats;
    int id, niveau, image, type;
    QString nom;
};

#endif // EQUIPABLE_H
