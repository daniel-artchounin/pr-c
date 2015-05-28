#ifndef PROGRAMMATIONTACHESIMPLEPREEMPTIVE_H
#define PROGRAMMATIONTACHESIMPLEPREEMPTIVE_H
# include "programmationtachesimple.h"
# include "duree.h"
#include "tachesimplepreemptive.h"

class ProgrammationTacheSimplePreemptive : public ProgrammationTacheSimple
{

protected :
    unsigned int pourcentage;
    TacheSimplePreemptive& tacheSimplePreemtive;

public:
    ProgrammationTacheSimplePreemptive(Date dateD, Horaire heureD, unsigned int pourc, TacheSimplePreemptive& tacheSimpleP):
        ProgrammationTacheSimple(dateD,heureD),
        pourcentage(pourc), tacheSimplePreemtive(tacheSimpleP){
        tacheSimplePreemtive.addProgrammation(this);
        tacheSimplePreemtive.addPourcentageComplete(pourc);


    }
    const TacheSimplePreemptive & getTacheSimple(){
        return tacheSimplePreemtive;
    }
    virtual const Duree& getDuree()const{
        return tacheSimplePreemtive.getDuree();
    }


    virtual ~ProgrammationTacheSimplePreemptive(){}

};
#endif // PROGRAMMATIONTACHESIMPLEPREEMPTIVE_H



