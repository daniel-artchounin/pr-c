#include "programmationtachesimple.h"
#include "programmationtachesimplepreemptive.h"

ProgrammationTacheSimplePreemptive::ProgrammationTacheSimplePreemptive(Date dateD, Horaire heureD, unsigned int pourc, TacheSimplePreemptive& tacheSimpleP):
    ProgrammationTacheSimple(dateD,heureD),
    pourcentage(pourc), tacheSimplePreemtive(tacheSimpleP){
    tacheSimplePreemtive.addProgrammation(this);
    tacheSimplePreemtive.addPourcentageComplete(pourc);


}

