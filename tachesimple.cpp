#include "tachesimple.h"
const Duree & TacheSimple::getDuree()const{
    return duree;
}
bool TacheSimple::isTermine()const{
    return termine;
}
void TacheSimple::setTermine(bool state){
    termine = state;
}
TacheSimple::TacheSimple(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
            const Horaire& heureEcheance,const std::string & titre,const Duree & dur)
    : Tache(dateD,heureD,dateEcheance,heureEcheance,titre),duree(dur),termine(false)
{

}
