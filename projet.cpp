#include "projet.h"
#include <typeinfo>
# include <string>

Projet::Projet(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
      const Horaire& heureEcheance,const std::string & titre):
    Element(dateD,heureD, titre, dateEcheance, heureEcheance),
    taches(0), nbTaches(0), nbTachesMax(0){
}

Tache** Projet::getTaches()const{
    return taches;
}

unsigned int Projet::getNbTaches()const{
    return nbTaches;
}

unsigned int Projet::getNbTachesMax()const{
    return nbTachesMax;
}
void Projet::addItem(Tache* t){
    if (nbTaches==nbTachesMax){
        Tache** newtab=new Tache*[nbTachesMax+10];
        for(unsigned int i=0; i<nbTaches; i++)
            newtab[i]= taches[i];
        nbTachesMax+=10;
        Tache** old= taches;
        taches=newtab;
        delete[] old;
    }
    taches[nbTaches++]=t;
}

Tache* Projet::trouverTache(const std::string& nomTache)const{
    for (unsigned int i = 0 ; i< nbTaches; i++){
        if(taches[i]->getTitre()==nomTache){
            return taches[i];
        }
    }
    return 0;
}
int Projet::trouverIndiceTache(const std::string& nomTache)const{
    for (unsigned int i = 0 ; i< nbTaches; i++){
        if(taches[i]->getTitre()==nomTache){
            return i;
        }
    }
    return -1;
}

Tache& Projet::ajouterTache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
                    const Horaire& heureEcheance,const std::string & titre,bool preemptive, bool composite, const Duree & dur){
    if(preemptive && composite){
        throw ProjetException("erreur : On ne peut pas créer de tâche composite et preemptive");
    }
    if (trouverTache(titre))
        throw ProjetException("erreur : TacheSimple deja existante");
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
    addItem(newTache);
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
    int i =trouverIndiceTache(titre);
    if (i == -1){
        throw TacheCompositeException("erreur : tache inexistante");
    }
    Tache * t = taches[i];
    if(nbTaches > 1){
        taches[i]= taches[nbTaches-1];
    }
    delete t;
    nbTaches--;
}

const Tache& Projet::accederTache(const std::string * nomsTachesComposites , unsigned int nbTaches,const std::string& nomTache, unsigned int profondeur, const TacheComposite* tacheCourante){
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
                throw ProjetException("Les titres de tâches données en paramètres ne sont pas des taches composites");
            }
            if(newTache == 0){
                throw ProjetException("erreur : tache inexistante");
            }
            return accederTache(nomsTachesComposites, nbTaches, nomTache, profondeur++,newTache);
        }
        else{
            // on cherche une tâche composite sous la tâche composite actuelle
            try{
                newTache = dynamic_cast<const TacheComposite *>(tacheCourante->trouverSsTache(nomsTachesComposites[profondeur]));
            }
            catch(std::bad_cast &e){
                throw ProjetException("Les titres de tâches données en paramètres ne sont pas des taches composites");
            }
            if(newTache == 0){
                throw ProjetException("erreur : tache inexistante");
            }
            return accederTache(nomsTachesComposites,nbTaches, nomTache, profondeur++,newTache);
        }
    }
}

bool Projet::verifierContraintesRespectees(const std::string * nomsTaches, unsigned int nbTaches, const Date& dateD
                                   ,const Horaire& heureD,const Date& dateF, const Horaire& heureF){
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
            throw ProjetException("Les titres de tâches données en paramètres ne sont pas des taches composites");
        }
    }
    return true;

}

Projet::~Projet(){
    for(unsigned int i = 0 ; i < nbTaches ; i++){
        delete taches[i];
    }
    delete[]taches;
}
