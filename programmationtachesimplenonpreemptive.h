#ifndef PROGRAMMATIONTACHESIMPLENONPREEMPTIVE_H
#define PROGRAMMATIONTACHESIMPLENONPREEMPTIVE_H
# include "programmationtachesimple.h"
# include "tachesimplenonpreemptive.h"
clas TacheSimpleNonPreemptive;
class ProgrammationTacheSimpleNonPreemptive : public ProgrammationTacheSimple
{
protected :
    TacheSimpleNonPreemptive* tacheSimpleNonPreemptive;
public:
    ProgrammationTacheSimpleNonPreemptive(const Date& dateD, const Horaire& heureD, TacheSimpleNonPreemptive& tacheSimpleNonP):
        ProgrammationTacheSimple(dateD,heureD), tacheSimpleNonPreemptive(&tacheSimpleNonP){
        tacheSimpleNonPreemptive->setProgrammation(this);

    }
    const TacheSimpleNonPreemptive & getTacheSimple(){
        return *tacheSimpleNonPreemptive;
    }
    virtual const Duree& getDuree()const{
        return tacheSimpleNonPreemptive->getDuree();
    }

    virtual ~ProgrammationTacheSimpleNonPreemptive(){}

};

#endif // PROGRAMMATIONTACHESIMPLENONPREEMPTIVE_H
