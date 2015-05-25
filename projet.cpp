#include "projet.h"
#include <typeinfo>
# include <string>

Projet::Projet(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
      const Horaire& heureEcheance,const std::string & titre):
    Manager<Tache>(),Element(titre, dateD, heureD, dateEcheance, heureEcheance)
{
}

/*Tache** Projet::getTaches()const{
    return taches;
}*/

/*unsigned int Projet::getNbTaches()const{
    return nbTaches;
}*/

/*unsigned int Projet::getNbTachesMax()const{
    return nbTachesMax;
}*/

Tache* Projet::trouverTache(const std::string& nomTache)const{
    return getItem(nomTache);
}

Tache& Projet::ajouterTache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
                    const Horaire& heureEcheance,const std::string & titre,bool preemptive, bool composite, const Duree & dur){
    if(preemptive && composite){
        throw ProjetException("erreur : On ne peut pas créer de tâche composite et preemptive");
    }
    if (trouverTache(titre))
        throw ProjetException("erreur : Tache deja existante");
    Tache* newTache = 0;
    if(preemptive){
        newTache = new TacheSimplePreemptive(dateD,heureD, dateEcheance, heureEcheance,
                                             titre,dur);
    }
    else if(!preemptive && !composite){
        newTache = new TacheSimpleNonPreemptive(dateD,heureD, dateEcheance, heureEcheance,
                                             titre,dur);
    }
    else{
        newTache = new TacheComposite(dateD,heureD, dateEcheance, heureEcheance,
                                             titre);
    }
    addItem(titre,newTache);
    return *newTache;
}

Tache& Projet::getTache(const std::string& titre){
    Tache* t=trouverTache(titre);
    if (!t) {
        throw ProjetException("erreur : tache inexistante");
    }
    return *t;
}

const Tache& Projet::getTache(const std::string& titre)const{
    return const_cast<Projet*>(this)->getTache(titre);
}

void Projet::supprimerTache(const std::string& titre){

    if(!trouverTache(titre)){
        throw TacheCompositeException("erreur : tache inexistante");
    }
    items.erase(titre);
}

const Tache& Projet::accederTache(const std::string * nomsTachesComposites , unsigned int nbTaches,
                                  const std::string& nomTache, unsigned int profondeur, const TacheComposite* tacheCourante){
    const TacheComposite* newTache = 0;
    if (nbTaches == 0){
        // la tâche recherchée se trouve directement à la racine du projet
        return getTache(nomTache);
    }
    else{
        // la tâche recherchée ne se trouve pas directement à la racine du projet
        if(profondeur == nbTaches){
            // la tâche recherchée est une sous tâche de la tâche composite actuelle
            return tacheCourante->getSsTache(nomTache);
        }
        else if(profondeur == 0){
            // on cherche une tâche composite à la racine du projet
            try{
                newTache = dynamic_cast<const TacheComposite*>(trouverTache(nomsTachesComposites[profondeur]));
            }
            catch(std::bad_cast& e){
                // on n'est normalement pas censé entrer ici car dynamic_cast ne génère pas d'exception pour les
                // conversions de pointeur
                throw ProjetException("Les titres de tâches données en paramètres ne sont pas des taches composites");
            }
            if(newTache == 0){
                throw ProjetException("Les titres de tâches données en paramètres ne sont pas des taches composites");
            }
            return accederTache(nomsTachesComposites, nbTaches, nomTache, profondeur++,newTache);
        }
        else{
            // on cherche une tâche composite sous la tâche composite actuelle
            try{
                newTache = dynamic_cast<const TacheComposite *>(tacheCourante->trouverSsTache(nomsTachesComposites[profondeur]));
            }
            catch(std::bad_cast &e){
                // on n'est normalement pas censé entrer ici car dynamic_cast ne génère pas d'exception pour les
                // conversions de pointeur
                throw ProjetException("Les titres de tâches données en paramètres ne sont pas des taches composites");
            }
            if(newTache == 0){
                throw ProjetException("Les titres de tâches données en paramètres ne sont pas des taches composites");
            }
            return accederTache(nomsTachesComposites,nbTaches, nomTache, profondeur++,newTache);
        }
    }
}

bool Projet::verifierContraintesRespectees(const std::string * nomsTaches, unsigned int nbTaches, const Date& dateD
                                   ,const Horaire& heureD,const Date& dateF, const Horaire& heureF)const{
    Tache* tacheActuelle = 0;
    TacheComposite* tacheCompositeActuelle = 0;
    for(unsigned int i = 0; i < nbTaches; i++){
        if(i==0){
            if( (dateD < dateDebut) || (dateF > dateFin)
                    ||( (dateD == dateDebut) && (heureD < horaireDebut) )
                    ||( (dateF == dateFin) && (heureF > horaireFin) )   ){
                    return false;
            }
            tacheActuelle = trouverTache(nomsTaches[i]);
        }
        else{
            if( (dateD < tacheCompositeActuelle->getDateDebut()) || (dateF > tacheCompositeActuelle->getDateFin())
                    ||( (dateD == tacheCompositeActuelle->getDateDebut()) && (heureD < tacheCompositeActuelle->getHoraireDebut()) )
                    ||( (dateF == tacheCompositeActuelle->getDateFin()) && (heureF > tacheCompositeActuelle->getHoraireFin()) )   ){
                    return false;
            }
            tacheActuelle = tacheCompositeActuelle->trouverSsTache(nomsTaches[i]);
        }
        if(tacheActuelle == 0){
            throw ProjetException("erreur : tache inexistante");
        }
        try{
            tacheCompositeActuelle = dynamic_cast<TacheComposite*>(tacheActuelle);
        }
        catch(std::bad_cast& e){
            // on n'est normalement pas censé entrer ici car dynamic_cast ne génère pas d'exception pour les
            // conversions de pointeur
            throw ProjetException("Les titres de tâches données en paramètres ne sont pas des taches composites");
        }
        if(tacheCompositeActuelle == 0){
            throw ProjetException("Les titres de tâches données en paramètres ne sont pas des taches composites");
        }
    }
    return true;

}

