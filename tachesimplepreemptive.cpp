#include "tachesimplepreemptive.h"
#include "tachesimplepreemptiveexception.h"
#include "programmationtachesimplepreemptive.h"
# include "programmationmanager.h"

void TacheSimplePreemptive::eraseProgrammation(const Date& dateProgrammation, const Horaire& horaireProgrammation){
    std::string cleProgrammationASupprimer = ProgrammationManager::getKeyFrom(dateProgrammation, horaireProgrammation);
    for(p_iterator it = pBegin() ; it != pEnd() ; ++it) {
        if(cleProgrammationASupprimer == ProgrammationManager::getKeyFrom((*it)->getDateProgrammation(), (*it)->getHoraireProgrammation())){
            programmationsTachesSimplesPreemptives.erase(it);
        }
    }
}

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
                   dur),pourcentageDejaProgramme(0),programmationsTachesSimplesPreemptives(){
}
unsigned int TacheSimplePreemptive::getPourcentageDejaProgramme()const{
    return pourcentageDejaProgramme;
}
void TacheSimplePreemptive::setPourcentageDejaProgramme(int prt){
    if (prt>100){
        throw TacheSimplePreemptiveException("Erreur : Le pourcentage est supérieur à 100 !");
    }else if(prt <0){
        throw TacheSimplePreemptiveException("Erreur : Le pourcentage est inférieur à 100 !");
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

void TacheSimplePreemptive::exportTo(QXmlStreamWriter& stream) {
    stream.writeStartElement("TachePreemptive");
    TacheSimple::exportTo(stream);
    stream.writeStartElement("ListeProgrammations");
    for(p_iterator it=pBegin(); it!=pEnd(); ++it) {
        (*it)->exportTo(stream);
    }
    stream.writeEndElement();
    stream.writeEndElement();
}

void TacheSimplePreemptive::exportProgrammations(QXmlStreamWriter& stream) {
    for(p_iterator it=pBegin(); it!=pEnd(); ++it) {
        (*it)->exportTo(stream);
    }
}

TacheSimplePreemptive::~TacheSimplePreemptive(){
    ProgrammationManager& programmationManager = ProgrammationManager::getInstance();
    while (!programmationsTachesSimplesPreemptives.empty())
    {
        programmationManager.eraseItem(programmationManager.getKeyFrom(
                                           programmationsTachesSimplesPreemptives.back()->getDateProgrammation(),
                                           programmationsTachesSimplesPreemptives.back()->getHoraireProgrammation()
                                           )
                                       );
        programmationsTachesSimplesPreemptives.pop_back();
    }
}
