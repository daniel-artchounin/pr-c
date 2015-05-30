#include "tachesimplenonpreemptive.h"
#include "tachesimplenonpreemptiveexception.h"
#include "programmationtachesimplenonpreemptive.h"
#include "tools.h"

TacheSimpleNonPreemptive::TacheSimpleNonPreemptive(const Date& dateD, const Horaire& heureD,
                                                   const Date& dateEcheance,
                                                   const Horaire& heureEcheance,
                                                   const std::string & titre,const Duree & dur)
    :TacheSimple(dateD, heureD, dateEcheance,
                  heureEcheance, titre, dur),programmationTacheSimpleNonPreemptive(0){
    if(!dureeValide(dur)){
        throw TacheSimpleNonPreemptiveException("La durée tansmise en paramètres n'est pas valide");
    }
}

bool TacheSimpleNonPreemptive::dureeValide(const Duree& duree)const{
    return duree < Duree(12,00);
}

bool TacheSimpleNonPreemptive::isEndProgrammationOk(const Date& dateProg, const Horaire& horaireProg)const{
    if(!hasProgrammation()){
        // la tache ne possède pas encore de programmation
        return false;
    }else{
        // récupération de la programmation
        if(programmationTacheSimpleNonPreemptive->getDateFin()<= dateProg ||
                (programmationTacheSimpleNonPreemptive->getDateFin()== dateProg && programmationTacheSimpleNonPreemptive->getHoraireFin() <= horaireProg) ){
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
        return false;
    }
    return true;
}

ProgrammationTacheSimpleNonPreemptive* TacheSimpleNonPreemptive::getProgrammation() const{
    return programmationTacheSimpleNonPreemptive;
}

void TacheSimpleNonPreemptive::exportTo(QXmlStreamWriter& stream) {
    stream.writeStartElement("TacheSimpleNonPreemptive");
    TacheSimple::exportTo(stream);
    stream.writeTextElement("duree",toQString(getDuree().toString()));
    stream.writeEndElement();
}
