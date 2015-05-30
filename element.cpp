#include "element.h"

Element::~Element(){}

const Duree & Element::getDuree()const{
    return duree;
}

bool Element::estDansIntervalle(const Date& dateProg, const Horaire& horaireProg){
    if( ( dateProg>=dateDebut || (dateProg==dateDebut && horaireProg >= horaireDebut) )
          && ( (dateFin-dateProg)*24*60+(horaireFin-horaireProg)-duree.getDureeEnMinutes() >= 0) ){
        return true;
    }
    return false;
}
