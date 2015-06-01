
#include "tachesimple.h"

TacheSimple::TacheSimple(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
            const Horaire& heureEcheance,const std::string & titre,const Duree & dur)
    : Tache(dateD,heureD,dateEcheance,heureEcheance,titre,dur){}
