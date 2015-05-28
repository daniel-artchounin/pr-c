#include "tache.h"
# include "tacheexception.h"

Tache::Tache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
      const Horaire& heureEcheance,const std::string & titre,const Duree& dur):
    Element(titre, dateD, heureD, dateEcheance, heureEcheance,dur),
    tachesPrecedentes(){
}

/*
Tache** Tache::getTachesPrecedentes()const{
    return tachesPrecedentes;
}
*/
/*size_type Tache::getNbTachesPrecedentes() const{
    return tachesPrecedentes.size();
}
*/
/*
int Tache::getNbTachesPrecedentesMax() const{
    return nbTachesPrecedentesMax;
}
*/


bool Tache::isTachePrecedente(const std::string& titre) const{
    Tache* tachePrecedente = trouverTachePrecedente(titre);
    if (tachePrecedente == 0){
        return false;
    }
    else{
        return true;
    }
}

Tache* Tache::trouverTachePrecedente(const std::string & titre)const{
    const_iterator2 result = tachesPrecedentes.find(titre);
    if(result == tPEnd()) {
        return 0;
    }
    return result->second;
}

void Tache::ajouterTachePrecedente(Tache & tachePrecedente){
    if(tachePrecedente.trouverTachePrecedente(tachePrecedente.getTitre())){
        throw TacheException("Erreur : la tâche envoyée en paramètre a pour tâche precedente la tâche courante");
    }
    //(date1-date2)*24*60+heure1-heure2)
    if( ((this->getDateFin()-tachePrecedente.getDateDebut())*24*60+(this->getHoraireFin()-tachePrecedente.getHoraireDebut()))
            -tachePrecedente.getDuree().getNbMinutes()< this->getDuree().getNbMinutes()){
        throw TacheException("Erreur : la tâche envoyée en paramètre ne sera pas programmable");
    }
    tachesPrecedentes.insert(std::pair<std::string, Tache*>(tachePrecedente.getTitre(), &tachePrecedente));
}

void Tache::supprimerTachesPrecedente(const std::string & tachePrecedente){
    if(!trouverTachePrecedente(tachePrecedente)){
        throw TacheException("Erreur : la tâche envoyée en paramètre ne précède pas la tâche actuelle");
    }
    tachesPrecedentes.erase(tachePrecedente);
}


