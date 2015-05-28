#ifndef PROGRAMMATIONTACHESIMPLENONPREEMPTIVE_H
#define PROGRAMMATIONTACHESIMPLENONPREEMPTIVE_H
# include "programmationtachesimple.h"
# include "tachesimplenonpreemptive.h"
class ProgrammationTacheSimpleNonPreemptive : public ProgrammationTacheSimple
{
protected :
    TacheSimpleNonPreemptive* tacheSimpleNonPreemptive;
public:
    ProgrammationTacheSimpleNonPreemptive(const Date& dateD, const Horaire& heureD, TacheSimpleNonPreemptive& tacheSimpleNonP);

    const TacheSimpleNonPreemptive & getTacheSimple();
    virtual const Duree& getDuree()const;

    virtual ~ProgrammationTacheSimpleNonPreemptive(){}

};

#endif // PROGRAMMATIONTACHESIMPLENONPREEMPTIVE_H
