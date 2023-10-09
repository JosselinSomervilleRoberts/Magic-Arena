#ifndef ARMURE_H
#define ARMURE_H

#include <QWidget>
#include "Equipable.h"

class Armure : public Equipable
{
    Q_OBJECT

public:
    Armure(int id);
};

#endif // ARMURE_H
