#include "element.h"
#include "tools.h"

Element::~Element(){}

const Duree & Element::getDuree()const{
    return duree;
}

bool Element::estDansIntervalle(const Date& dateProg, const Horaire& horaireProg, unsigned int pourcentage){
    std::cout << (((dateFin-dateProg)*24*60+(horaireFin-horaireProg))-int(duree.getDureeEnMinutes()));
    if( ( dateProg>=dateDebut || (dateProg==dateDebut && horaireProg >= horaireDebut) )
          && ( ( (dateFin-dateProg)*24*60+(horaireFin-horaireProg)-( (pourcentage * int(getDuree().getDureeEnMinutes()) )/100) ) >= 0) ){
        return true;
    }
    return false;
}

void Element::exportTo(QXmlStreamWriter& stream) {
    stream.writeTextElement("titre",toQString(getTitre()));
    stream.writeTextElement("dateDebut",toQString(getDateDebut().toString()));
    stream.writeTextElement("horaireDebut",toQString(getHoraireDebut().toString()));
    stream.writeTextElement("dateFin",toQString(getDateFin().toString()));
    stream.writeTextElement("horaireFin",toQString(getHoraireFin().toString()));
    stream.writeTextElement("duree",toQString(getDuree().toString()));
}
