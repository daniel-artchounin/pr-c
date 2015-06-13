#include "tachesimplepreemptive.h"
#include "tachesimplepreemptiveexception.h"
#include "programmationtachesimplepreemptive.h"
# include "programmationmanager.h"

void TacheSimplePreemptive::eraseProgrammation(const Date& dateProgrammation, const Horaire& horaireProgrammation){
    std::string cleProgrammationASupprimer = ProgrammationManager::getKeyFrom(dateProgrammation, horaireProgrammation); // on récupère la clé de la programmation à supprimer
    p_iterator it = pBegin();
    for(unsigned int i = 0; i < programmationsTachesSimplesPreemptives.size() ; ++i) {
        if(cleProgrammationASupprimer == ProgrammationManager::getKeyFrom(programmationsTachesSimplesPreemptives[i]->getDateProgrammation(), programmationsTachesSimplesPreemptives[i]->getHoraireProgrammation())){
            // s'il s'agit de la tâche à supprimer, on l'efface
            programmationsTachesSimplesPreemptives.erase(it);
        }
        ++it;
    }
}

bool TacheSimplePreemptive::hasProgrammation()const{
    return programmationsTachesSimplesPreemptives.size()!=0;
}

void TacheSimplePreemptive::addPourcentageDejaProgramme(int prt){
    if (prt>100){
        throw TacheSimplePreemptiveException("Erreur : Le pourcentage est supérieur à 100 !");
    }else if(prt <0){
        throw TacheSimplePreemptiveException("Erreur : Le pourcentage est inférieur à 100 !");
    }
    setPourcentageDejaProgramme(getPourcentageDejaProgramme() + (unsigned int)prt);
}

void TacheSimplePreemptive::addProgrammation(ProgrammationTacheSimplePreemptive * pgrm){
    programmationsTachesSimplesPreemptives.push_back(pgrm);
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
    else{
        pourcentageDejaProgramme = (unsigned int) prt;
    }
}

bool TacheSimplePreemptive::isEndProgrammationOk(const Date& dateProg, const Horaire& horaireProg)const{
    if(!hasProgrammation() || pourcentageDejaProgramme != 100){
        // la tache ne possède pas encore de programmation ou elle n'as pas encore totalement été programmée
        return false;
    }else{
        // la tache préemptive a été totalement programmée
        ProgrammationTacheSimplePreemptive * lastProgrammation = programmationsTachesSimplesPreemptives.back(); // récupération de la dernière programmation
        if(lastProgrammation->getDateFin()< dateProg ||
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
            return *it; // on retourne un pointeur sur une ProgrammationTacheSimplePreemptive si on a trouvé la tâche cherchée
        }
    }
    return 0; // on retourne si on a pas trouvé la programmation recherchée
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
    while (programmationsTachesSimplesPreemptives.size()!=0)
    {
        // on supprime toutes les programmations de la tâche simple préemptive lors de sa destruction
        programmationManager.eraseItem(programmationManager.getKeyFrom(
                                           programmationsTachesSimplesPreemptives.back()->getDateProgrammation(),
                                           programmationsTachesSimplesPreemptives.back()->getHoraireProgrammation()
                                           )
                                       );
    }
}
