#ifndef INFORMATIONSTACHESIMPLE_H
#define INFORMATIONSTACHESIMPLE_H
# include "informationstache.h"
# include "tachesimple.h"


class InformationsTacheSimple : public InformationsTache
{
protected:
public:
    InformationsTacheSimple(const TacheSimple& tacheSimple, QWidget *parent = 0);
};

#endif // INFORMATIONSTACHESIMPLE_H
