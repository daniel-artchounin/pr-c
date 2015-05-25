#include "tachecomposite.h"


TacheComposite::TacheComposite(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
      const Horaire& heureEcheance,const std::string & titre):
    Manager<Tache>(),Tache(dateD, heureD, dateEcheance,heureEcheance,
          titre){
}
/*Tache** TacheComposite::getSsTaches() const{
    return ssTaches;
}*/
/*int TacheComposite::getnbSsTaches(){
    return nbSsTaches;
}*/
/*int TacheComposite::getnbSsTachesMax(){
    return nbSsTachesMax;
}*/

Tache* TacheComposite::trouverSsTache(const std::string& nomTache)const{
    return getItem(nomTache);
}

Tache& TacheComposite::ajouterSsTache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
                    const Horaire& heureEcheance,const std::string & titre,const Duree & dur, bool preemptive){
    if (trouverSsTache(titre))
        throw TacheCompositeException("erreur : TacheSimple deja existante");
    Tache* newTache = 0;
    if(preemptive){
        newTache = new TacheSimplePreemptive(dateD,heureD, dateEcheance, heureEcheance,
                                             titre,dur);

    }
    else{
        try{
            newTache = new TacheSimpleNonPreemptive(dateD,heureD, dateEcheance, heureEcheance,
                                                 titre,dur);

        }catch (TacheSimpleNonPreemptiveException& e){
            delete newTache;
        }

    }
    if(!addItem(titre,newTache)){
        delete newTache;
        throw TacheCompositeException("erreur : Nous n'avons pas réussi à ajouter la tâche à tâche composite");
    }
    return *newTache;
}

Tache& TacheComposite::getSsTache(const std::string& titre){
    Tache* t=trouverSsTache(titre);
    if (!t) {
        throw TacheCompositeException("erreur : tache inexistante");
    }
    return *t;
}

const Tache& TacheComposite::getSsTache(const std::string& titre)const{
    return const_cast<TacheComposite*>(this)->getSsTache(titre);
}

void TacheComposite::supprimerSsTache(const std::string& titre){
    if(!trouverSsTache(titre)){
        throw TacheCompositeException("Erreur : la tâche envoyée en paramètre ne précède pas la tâche actuelle");
    }
    items.erase(titre);
}

bool TacheComposite::isTermine()const{
    for(const_iterator it = begin(); it != end(); ++it){
        if(!(it->second->isTermine())){
            return false;
        }
    }
    return true;
}

