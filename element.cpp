#include "element.h"
#include "tools.h"

Element::~Element(){}

const Duree & Element::getDuree()const{
    return duree;
}

bool Element::estDansIntervalle(const Date& dateProg, const Horaire& horaireProg){
    if( ( dateProg>=dateDebut || (dateProg==dateDebut && horaireProg >= horaireDebut) )
          && ( ( (dateFin-dateProg)*24*60+(horaireFin-horaireProg)-int(duree.getDureeEnMinutes()) ) >= 0) ){
        return true;
    }
    return false;
}

void Element::exportTo(QXmlStreamWriter& stream) {
    stream.writeTextElement("titre",toQString(titre));
    stream.writeTextElement("dateDebut",toQString(dateDebut.toString()));
    stream.writeTextElement("horaireDebut",toQString(horaireDebut.toString()));
    stream.writeTextElement("dateFin",toQString(dateFin.toString()));
    stream.writeTextElement("horaireFin",toQString(horaireFin.toString()));
    stream.writeTextElement("duree",toQString(duree.toString()));
}
