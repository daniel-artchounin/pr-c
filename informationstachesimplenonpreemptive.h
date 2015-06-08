#ifndef INFORMATIONSTACHESIMPLENONPREEMPTIVE_H
#define INFORMATIONSTACHESIMPLENONPREEMPTIVE_H
# include "informationstachesimple.h"
# include "tachesimplenonpreemptive.h"

class InformationsTacheSimpleNonPreemptive : public InformationsTacheSimple
{
protected:
    QLabel *dateDebutP;
    QLabel *horaireDebutP;
    QLabel *dateEcheanceP;
    QLabel *heureEcheanceP;
public:
    InformationsTacheSimpleNonPreemptive(const TacheSimpleNonPreemptive& tacheSimpleNonPreemptive, QWidget *parent = 0);
};

#endif // INFORMATIONSTACHESIMPLENONPREEMPTIVE_H
