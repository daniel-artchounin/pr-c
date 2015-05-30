#include "programmation.h"
#include "tools.h"

Programmation::~Programmation(){}

void Programmation::exportTo(QXmlStreamWriter& stream) {
    stream.writeTextElement("dateProgrammation",toQString(dateProg.toString()));
    stream.writeTextElement("horaireProgrammation",toQString(horaireProg.toString()));
    stream.writeTextElement("dateEcheance",toQString(getDateFin().toString()));
    stream.writeTextElement("horaireEcheance",toQString(getHoraireFin().toString()));
    stream.writeTextElement("duree",toQString(getDuree().toString()));
}

