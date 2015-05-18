#include "tachesimplenonpreemptive.h"

TacheSimpleNonPreemptive::TacheSimpleNonPreemptive(const Date& dateD, const Horaire& heureD,
                                                   const Date& dateEcheance,
                                                   const Horaire& heureEcheance,
                                                   const std::string & titre,const Duree & dur)
    :TacheSimple(dateD, heureD, dateEcheance,
                  heureEcheance, titre, dur){
    if(!dureeValide(dur)){
        throw TacheSimpleNonPreemptiveException("La durée tansmise en paramètres n'est pas valide");
    }
}

bool TacheSimpleNonPreemptive::dureeValide(const Duree& duree){
    return duree < Duree(12,00);
}
