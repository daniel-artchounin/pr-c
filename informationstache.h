#ifndef INFORMATIONSTACHE_H
#define INFORMATIONSTACHE_H
# include "informationselement.h"
# include "tache.h"

class InformationsTache : public InformationsElement
{
public:
    InformationsTache(const Tache& tache, QWidget *parent = 0);
};

#endif // INFORMATIONSTACHE_H
