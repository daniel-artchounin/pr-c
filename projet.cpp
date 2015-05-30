#include "projet.h"
#include "tachesimplepreemptive.h"
#include "tachesimplenonpreemptive.h"
#include "tachesimplenonpreemptiveexception.h"
#include "tachecompositeexception.h"
#include <typeinfo>
#include "projetexception.h"

Projet::Projet(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
      const Horaire& heureEcheance,const std::string & titre):
    Manager<Tache>(),Element(titre, dateD, heureD, dateEcheance, heureEcheance){}

Tache* Projet::trouverTache(const std::string& nomTache)const{
    return getItem(nomTache);
}

void Projet::ajouterTache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
                    const Horaire& heureEcheance,const std::string & titre,bool preemptive, bool composite, const Duree & dur){
    if(preemptive && composite){
        throw ProjetException("erreur : On ne peut pas créer de tâche composite et preemptive");
    }
    Tache* newTache = 0;
    if(preemptive){
        newTache = new TacheSimplePreemptive(dateD,heureD, dateEcheance, heureEcheance,
                                             titre,dur);
    }
    else if(!preemptive && !composite){
        try{
            newTache = new TacheSimpleNonPreemptive(dateD,heureD, dateEcheance, heureEcheance,
                                             titre,dur);
        }catch (TacheSimpleNonPreemptiveException& e){
            delete newTache;
            throw ProjetException("La tache possède une durée supérieur à 12 heures");
        }
        newTache = new TacheSimpleNonPreemptive(dateD,heureD, dateEcheance, heureEcheance,
                                             titre,dur);
    }
    else{
        newTache = new TacheComposite(dateD,heureD, dateEcheance, heureEcheance,
                                             titre);
    }
    if(!addItem(titre,newTache)){
        delete newTache;
        throw TacheCompositeException("erreur : Nous n'avons pas réussi à ajouter la tâche au projet");
    }
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
                                  const std::string& nomTache, unsigned int profondeur, const TacheComposite* tacheCourante)const{
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
                                   ,const Horaire& heureD,const Date& dateF, const Horaire& heureF,const Duree & dur)const{
    if(dateF< dateD || (dateF==dateD && heureF < heureD )){
        return false;
    }
    if(((dateF-dateD)*24*60 + (heureF-heureD)) < int(dur.getDureeEnMinutes())){
        return false;
    }
    if(nbTaches == 0){
        if (trouverTache(titre)){
            throw ProjetException("erreur : Tache deja existante");
            return false;
        }
    }
    if( (dateD < dateDebut)
            || (dateF > dateFin)
            ||( (dateD == dateDebut) && (heureD < horaireDebut) )
            ||( (dateF == dateFin) && (heureF > horaireFin) )  ){
            return false;
    }
    Tache* tacheActuelle = 0;
    TacheComposite* tacheCompositeActuelle = 0;
    for(unsigned int i = 0; i < nbTaches; i++){
        // std::cout<<"bonjour"<<std::endl;
        if(i==0){

            if( nbTaches == 0 && ( ( ( (getDateFin()-getDateDebut())*24*60 + (getHoraireFin()-getHoraireDebut()) ) - int(getDuree().getDureeEnMinutes()) ) < int(dur.getDureeEnMinutes()) ) ) {
                return false; // la duree de la tâche est supérieur à la durée libre du projet
            }
            tacheActuelle = trouverTache(nomsTaches[i]);
        }
        else{
            // std::cout<< (tacheCompositeActuelle->getHoraireFin()-tacheCompositeActuelle->getHoraireDebut() )<<std::endl ;
            // std::cout<<i<<std::endl ;
            // std::cout<< "coucou"<<std::endl ;
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
        if( (dateD < tacheCompositeActuelle->getDateDebut()) || (dateF > tacheCompositeActuelle->getDateFin())
                ||( (dateD == tacheCompositeActuelle->getDateDebut()) && (heureD < tacheCompositeActuelle->getHoraireDebut()) )
                ||( (dateF == tacheCompositeActuelle->getDateFin()) && (heureF > tacheCompositeActuelle->getHoraireFin()) )   ){
                return false;
        }
        if( ( (nbTaches-1) == i) && ( ( ( (tacheCompositeActuelle->getDateFin()-tacheCompositeActuelle->getDateDebut())*24*60 +
                (tacheCompositeActuelle->getHoraireFin()-tacheCompositeActuelle->getHoraireDebut()) ) -
              int(tacheCompositeActuelle->getDuree().getDureeEnMinutes()) ) < int(dur.getDureeEnMinutes()) ) ){
            return false; // la duree de la tâche est supérieur à la durée libre de la tâche composite
        }
    }
    return true;

}

void Projet::creerAjouterTache(const std::string * nomsTaches, unsigned int nbTaches, const Date& dateD
                                   ,const Horaire& heureD,const Date& dateF, const Horaire& heureF,
                               const std::string& titre, bool preemptive, bool composite,const Duree & dur){
    if(!verifierContraintesRespectees(nomsTaches,nbTaches, dateD,heureD, dateF, heureF, dur)){
        throw ProjetException("ProjetException, création de la tâche " + titre + " impossible : contraintes non respectées");
    }
    Tache* tacheActuelle = 0;
    TacheComposite* tacheCompositeActuelle = 0;
    if(nbTaches==0){
        addDuree(dur); // on ajoute la durée de la tache au projet
        ajouterTache(dateD,heureD,dateF, heureF, titre, preemptive, composite, dur);
    }
    else {
        for(unsigned int i = 0; i < nbTaches; i++){
            if(i==0){
                tacheActuelle = trouverTache(nomsTaches[i]);
            }
            else{
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
        // std::cout<< (tacheCompositeActuelle->getHoraireFin()-tacheCompositeActuelle->getHoraireDebut() )<<std::endl ;
        tacheCompositeActuelle->addDuree(dur); // on ajoute la durée de la tache à celle de la tache composite
        // std::cout<< (tacheCompositeActuelle->getDuree())<<std::endl ;
        tacheCompositeActuelle->ajouterSsTache(dateD,heureD,dateF, heureF, titre, preemptive, composite, dur);

    }
}


