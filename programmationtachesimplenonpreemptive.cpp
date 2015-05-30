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

ProgrammationTacheSimpleNonPreemptive::~ProgrammationTacheSimpleNonPreemptive(){}

void ProgrammationTacheSimpleNonPreemptive::exportTo(QXmlStreamWriter& stream) {
    stream.writeStartElement("ProgrammationTacheSimpleNonPreemptive");
    ProgrammationTacheSimple::exportTo(stream);
    stream.writeEndElement();
}
