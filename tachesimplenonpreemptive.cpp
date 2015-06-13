#include "tachesimplenonpreemptive.h"
#include "tachesimplenonpreemptiveexception.h"
#include "programmationtachesimplenonpreemptive.h"
#include "tools.h"
# include "programmationmanager.h"

void TacheSimpleNonPreemptive::eraseProgrammation(){
    if (programmationTacheSimpleNonPreemptive !=0){
        programmationTacheSimpleNonPreemptive = 0;
    }
}

TacheSimpleNonPreemptive::TacheSimpleNonPreemptive(const Date& dateD, const Horaire& heureD,
                                                   const Date& dateEcheance,
                                                   const Horaire& heureEcheance,
                                                   const std::string & titre,const Duree & dur)
    :TacheSimple(dateD, heureD, dateEcheance,
                  heureEcheance, titre, dur),programmationTacheSimpleNonPreemptive(0){
    if(!dureeValide(dur)){
        // la durée est supréieure ou égale à 12 h 00
        throw TacheSimpleNonPreemptiveException("Erreur : la durée tansmise en paramètres n'est pas valide");
    }
}

bool TacheSimpleNonPreemptive::dureeValide(const Duree& duree)const{
    return duree < Duree(12,00); // retourne vrai si la durée est strictement inférieure à 12 h 00
}

bool TacheSimpleNonPreemptive::isEndProgrammationOk(const Date& dateProg, const Horaire& horaireProg)const{
    if(!hasProgrammation()){
        // la tache ne possède pas encore de programmation
        return false;
    }else{
        // la tache possède une programmation
        if(programmationTacheSimpleNonPreemptive->getDateFin()< dateProg ||
                (programmationTacheSimpleNonPreemptive->getDateFin() == dateProg && programmationTacheSimpleNonPreemptive->getHoraireFin() <= horaireProg) ){
            return true;
        }
        // la programmation ne sera pas terminée avant le début de notre prévision de programmation
        return false;
    }
}

void TacheSimpleNonPreemptive::setProgrammation(ProgrammationTacheSimpleNonPreemptive* programmationTacheSimpleNonP){
    programmationTacheSimpleNonPreemptive = programmationTacheSimpleNonP;
}

bool TacheSimpleNonPreemptive::hasProgrammation()const{
    if(programmationTacheSimpleNonPreemptive==0){
        return false; // la tâche n'a pas de programmation
    }
    return true; // la tâche a une programmation
}

ProgrammationTacheSimpleNonPreemptive* TacheSimpleNonPreemptive::getProgrammation() const{
    return programmationTacheSimpleNonPreemptive;
}

void TacheSimpleNonPreemptive::exportTo(QXmlStreamWriter& stream) {
    stream.writeStartElement("TacheSimpleNonPreemptive");
    TacheSimple::exportTo(stream);
    stream.writeStartElement("ListeProgrammations");
    if(programmationTacheSimpleNonPreemptive) {
        programmationTacheSimpleNonPreemptive->exportTo(stream);
    }
    stream.writeEndElement();
    stream.writeEndElement();
}

void TacheSimpleNonPreemptive::exportProgrammations(QXmlStreamWriter& stream) {
    if(programmationTacheSimpleNonPreemptive) {
        programmationTacheSimpleNonPreemptive->exportTo(stream);
    }
}

TacheSimpleNonPreemptive::~TacheSimpleNonPreemptive(){
    ProgrammationManager& programmationManager = ProgrammationManager::getInstance();
    if(programmationTacheSimpleNonPreemptive!=0){
        // on efface la programmation de la tâche à sa destruction et si cette dernière en a une
        programmationManager.eraseItem(programmationManager.getKeyFrom(programmationTacheSimpleNonPreemptive->getDateProgrammation(), programmationTacheSimpleNonPreemptive->getHoraireProgrammation()));
        programmationTacheSimpleNonPreemptive = 0;
    }
}
