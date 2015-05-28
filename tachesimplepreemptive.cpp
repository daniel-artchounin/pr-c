#include "tachesimplepreemptive.h"

TacheSimplePreemptive::TacheSimplePreemptive(const Date& dateD,
                      const Horaire& heureD,
                      const Date& dateEcheance,
                      const Horaire& heureEcheance,
                      const std::string & titre,
                      const Duree & dur):
       TacheSimple(dateD,
                   heureD,
                   dateEcheance,
                   heureEcheance,
                   titre,
                   dur),pourcentageComplete(0){
}
unsigned int TacheSimplePreemptive::getPourcentageComplete()const{
    return pourcentageComplete;
}
void TacheSimplePreemptive::setPourcentageComplete(int prt){
    pourcentageComplete = prt;
}

bool TacheSimplePreemptive::isEndProgrammationOk(const Date& dateProg, const Horaire& horaireProg)const{
    if(!hasProgrammation() || pourcentageComplete != 100){
        // la tache ne possède pas encore de programmation ou elle n'as pas encore totalement été programmée
        return false;
    }else{
        // la tache préemptive a été totalement programmée
        // récupération de la dernière programmation
        ProgrammationTacheSimplePreemptive * lastProgrammation = programmationstachessimplespreemptives.back();
        if(lastProgrammation->getDateFin()<= dateProg ||
                (lastProgrammation->getDateFin()== dateProg && lastProgrammation->getHoraireFin() <= horaireProg) ){
            return true;
        }
        // la dernière programmation ne sera pas terminée avant le début de notre prévision de programmation
        return false;

    }

}
