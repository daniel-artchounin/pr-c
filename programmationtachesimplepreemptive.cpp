#include "programmationtachesimplepreemptive.h"
#include "tachesimplepreemptive.h"
#include "tools.h"

Duree ProgrammationTacheSimplePreemptive::getDuree()const{
    return tacheSimplePreemtive->getDureeProgrammationViaPourcentage(pourcentage);
}

std::string ProgrammationTacheSimplePreemptive::getNom() const {
    return tacheSimplePreemtive->getTitre();
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
    if(tacheSimplePreemtive != 0){
        tacheSimplePreemtive->eraseProgrammation(getDateProgrammation(), getHoraireProgrammation());
    }
}

void ProgrammationTacheSimplePreemptive::exportTo(QXmlStreamWriter& stream) {
    stream.writeStartElement("ProgrammationTacheSimplePreemptive");
    ProgrammationTacheSimple::exportTo(stream);
    stream.writeTextElement("pourcentage",toQString(pourcentage));
    stream.writeEndElement();
}
