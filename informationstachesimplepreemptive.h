#ifndef INFORMATIONSTACHESIMPLEPREEMPTIVE_H
#define INFORMATIONSTACHESIMPLEPREEMPTIVE_H

# include "informationstachesimple.h"
# include "tachesimplepreemptive.h"

class InformationsTacheSimplePreemptive : public InformationsTacheSimple
{
protected :
    QTableWidget* programmationsTableWidget;
public:
    InformationsTacheSimplePreemptive(const TacheSimplePreemptive& tacheSimplePreemptive, QWidget *parent = 0);
};

#endif // INFORMATIONSTACHESIMPLEPREEMPTIVE_H
