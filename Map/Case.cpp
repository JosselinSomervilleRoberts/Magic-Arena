#include "Case.h"

Case::Case()
{}

Case::Case(int xRecu, int yRecu)
{
    setX(xRecu);
    setY(yRecu);
}

Case::Case(int xRecu, int yRecu, int accesRecu)
{
    setX(xRecu);
    setY(yRecu);
    setAcces(accesRecu);
}
