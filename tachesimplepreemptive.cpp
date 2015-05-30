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
                   dur),pourcentageDejaProgramme(0){
}
unsigned int TacheSimplePreemptive::getPourcentageDejaProgramme()const{
    return pourcentageDejaProgramme;
}
void TacheSimplePreemptive::setPourcentageDejaProgramme(int prt){
    if (prt>100){
        throw TacheSimplePreemptiveException("setPourcentageDejaProgramme : Le pourcentage est supérieur à 100 !");
    }else if(prt <0){
        throw TacheSimplePreemptiveException("setPourcentageDejaProgramme : Le pourcentage est inférieur à 100 !");
    }
    else
    pourcentageDejaProgramme = prt;
}

bool TacheSimplePreemptive::isEndProgrammationOk(const Date& dateProg, const Horaire& horaireProg)const{
    if(!hasProgrammation() || pourcentageDejaProgramme != 100){
        // la tache ne possède pas encore de programmation ou elle n'as pas encore totalement été programmée
        return false;
    }else{
        // la tache préemptive a été totalement programmée
        // récupération de la dernière programmation
        ProgrammationTacheSimplePreemptive * lastProgrammation = programmationsTachesSimplesPreemptives.back();
        if(lastProgrammation->getDateFin()<= dateProg ||
                (lastProgrammation->getDateFin()== dateProg && lastProgrammation->getHoraireFin() <= horaireProg) ){
            return true;
        }
        // la dernière programmation ne sera pas terminée avant le début de notre prévision de programmation
        return false;
    }
}

ProgrammationTacheSimplePreemptive* TacheSimplePreemptive::getProgrammation(const Date&  dateDebut, const Horaire& horaireDebut) const{
    for(p_const_iterator it = pBegin(); it != pEnd();++it){
        if( ( (*it)->getDateProgrammation() == dateDebut )  && ( (*it)->getHoraireProgrammation() == horaireDebut ) ){
            return *it;
        }
    }
    return 0;
}

