#ifndef INFORMATIONSTACHESIMPLENONPREEMPTIVE_H
#define INFORMATIONSTACHESIMPLENONPREEMPTIVE_H
# include "informationstachesimple.h"

class InformationsTacheSimpleNonPreemptive : public InformationsTacheSimple
{
public:
    InformationsTacheSimpleNonPreemptive(const TacheSimple& tacheSimple, QWidget *parent = 0);
};

#endif // INFORMATIONSTACHESIMPLENONPREEMPTIVE_H
