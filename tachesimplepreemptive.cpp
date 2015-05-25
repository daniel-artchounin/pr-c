#include "tachesimplepreemptive.h"

TacheSimplePreemptive::TacheSimplePreemptive(const Date& dateD,
                      const Horaire& heureD,
                      const Date& dateEcheance,
                      const Horaire& heureEcheance,
                      const std::string & titre,
                      const Duree & dur):
       TacheSimple(dateD,
                   heureD,
                   dateEcheance,
                   heureEcheance,
                   titre,
                   dur),pourcentageComplete(0){
}
unsigned int TacheSimplePreemptive::getPourcentageComplete()const{
    return pourcentageComplete;
}
void TacheSimplePreemptive::setPourcentageComplete(int prt){
    pourcentageComplete = prt;
}
