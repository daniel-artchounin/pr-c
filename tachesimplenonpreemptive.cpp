#include "tachesimplenonpreemptive.h"

TacheSimpleNonPreemptive::TacheSimpleNonPreemptive(const Date& dateD, const Horaire& heureD,
                                                   const Date& dateEcheance,
                                                   const Horaire& heureEcheance,
                                                   const std::string & titre,const Duree & dur)
    :TacheSimple(dateD, heureD, dateEcheance,
                  heureEcheance, titre, dur)
{
}
