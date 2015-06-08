#include "programmationtachesimplenonpreemptive.h"
#include "tachesimplenonpreemptive.h"

ProgrammationTacheSimpleNonPreemptive::ProgrammationTacheSimpleNonPreemptive(const Date& dateD, const Horaire& heureD, TacheSimpleNonPreemptive& tacheSimpleNonP):
    ProgrammationTacheSimple(dateD,heureD), tacheSimpleNonPreemptive(&tacheSimpleNonP){
    tacheSimpleNonPreemptive->setProgrammation(this);

}

const TacheSimpleNonPreemptive& ProgrammationTacheSimpleNonPreemptive::getTacheSimple()const{
    return *tacheSimpleNonPreemptive;
}

Duree ProgrammationTacheSimpleNonPreemptive::getDuree()const{
    return tacheSimpleNonPreemptive->getDuree();
}

std::string ProgrammationTacheSimpleNonPreemptive::getNom() const {
    return tacheSimpleNonPreemptive->getTitre();
}

ProgrammationTacheSimpleNonPreemptive::~ProgrammationTacheSimpleNonPreemptive(){
    if(tacheSimpleNonPreemptive !=0 ){
        tacheSimpleNonPreemptive->eraseProgrammation();
    }
}

void ProgrammationTacheSimpleNonPreemptive::exportTo(QXmlStreamWriter& stream) {
    stream.writeStartElement("ProgrammationTacheSimpleNonPreemptive");
    ProgrammationTacheSimple::exportTo(stream);
    stream.writeEndElement();
}
