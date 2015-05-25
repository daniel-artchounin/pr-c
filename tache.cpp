#include "tache.h"
# include "tacheexception.h"

Tache::Tache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
      const Horaire& heureEcheance,const std::string & titre):
    Element(titre, dateD, heureD, dateEcheance, heureEcheance),
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

bool Tache::finTachesPrecedentes() const{
    for (const_iterator2 it= tPBegin() ; it != tPEnd(); ++it){
        if(!(it->second->isTermine())){
            return false;
        }
    }
    return true;
}

bool Tache::isTachePrecedente(const Tache& tachePotentPrecedente) const{
    Tache* tachePrecedente = trouverTachePrecedente(tachePotentPrecedente);
    if (tachePrecedente == 0){
        return false;
    }
    else{
        return true;
    }
}

Tache* Tache::trouverTachePrecedente(const Tache& tachePotentPrecedente)const{
    std::string titre = tachePotentPrecedente.getTitre();
    const_iterator2 result = tachesPrecedentes.find(titre);
    if(result == tPEnd()){
        return 0;
    }
    return result->second;
}

void Tache::ajouterTachePrecedente(Tache & tachePrecedente){
    if(tachePrecedente.trouverTachePrecedente(*this)){
        throw TacheException("Erreur : la tâche envoyée en paramètre a pour tâche precedente la tâche courante");
    }
    tachesPrecedentes.insert(std::pair<std::string, Tache*>(tachePrecedente.getTitre(), &tachePrecedente));
}

void Tache::supprimerTachesPrecedente(const Tache & tachePrecedente){
    if(!trouverTachePrecedente(tachePrecedente)){
        throw TacheException("Erreur : la tâche envoyée en paramètre ne précède pas la tâche actuelle");
    }
    tachesPrecedentes.erase(tachePrecedente.getTitre());
}
