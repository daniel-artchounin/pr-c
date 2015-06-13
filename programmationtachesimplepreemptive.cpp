#include "programmationtachesimplepreemptive.h"
#include "tachesimplepreemptive.h"
#include "tools.h"

Duree ProgrammationTacheSimplePreemptive::getDuree()const{
    return tacheSimplePreemptive->getDureeProgrammationViaPourcentage(pourcentage);
}

std::string ProgrammationTacheSimplePreemptive::getNom() const {
    return tacheSimplePreemptive->getTitre();
}

TacheSimplePreemptive& ProgrammationTacheSimplePreemptive::getTacheSimple() const{
    return *tacheSimplePreemptive;
}

ProgrammationTacheSimplePreemptive::ProgrammationTacheSimplePreemptive(const Date& dateD, const Horaire& heureD, unsigned int pourc, TacheSimplePreemptive& tacheSimpleP):
    ProgrammationTacheSimple(dateD,heureD),
    pourcentage(pourc), tacheSimplePreemptive(&tacheSimpleP){
    tacheSimplePreemptive->addProgrammation(this);
    tacheSimplePreemptive->addPourcentageDejaProgramme(pourc);
}

ProgrammationTacheSimplePreemptive::~ProgrammationTacheSimplePreemptive(){
    if(tacheSimplePreemptive != 0){
        tacheSimplePreemptive->eraseProgrammation(getDateProgrammation(), getHoraireProgrammation());
    }
}

void ProgrammationTacheSimplePreemptive::exportTo(QXmlStreamWriter& stream) {
    stream.writeStartElement("ProgrammationTacheSimplePreemptive");
    ProgrammationTacheSimple::exportTo(stream);
    stream.writeTextElement("pourcentage",toQString(pourcentage));
    stream.writeEndElement();
}
