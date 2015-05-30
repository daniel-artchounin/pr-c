#include "programmationtachesimplepreemptive.h"

Duree ProgrammationTacheSimplePreemptive::getDuree()const{
    return tacheSimplePreemtive->getDureeProgrammationViaPourcentage(pourcentage);
}

const TacheSimplePreemptive& ProgrammationTacheSimplePreemptive::getTacheSimple() const{
    return *tacheSimplePreemtive;
}

ProgrammationTacheSimplePreemptive::ProgrammationTacheSimplePreemptive(const Date& dateD, const Horaire& heureD, unsigned int pourc, TacheSimplePreemptive& tacheSimpleP):
    ProgrammationTacheSimple(dateD,heureD),
    pourcentage(pourc), tacheSimplePreemtive(&tacheSimpleP){
    tacheSimplePreemtive->addProgrammation(this);
    tacheSimplePreemtive->addPourcentageDejaProgramme(pourc);
}


ProgrammationTacheSimplePreemptive::~ProgrammationTacheSimplePreemptive(){

}
