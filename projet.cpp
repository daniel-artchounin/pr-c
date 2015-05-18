#include "projet.h"

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

Tache* Projet::trouverTache(const std::string& nomTache){
    for (unsigned int i = 0 ; i< nbTaches; i++){
        if(taches[i]->getTitre()==nomTache){
            return taches[i];
        }
    }
    return 0;
}
int Projet::trouverIndiceTache(const std::string& nomTache){
    for (unsigned int i = 0 ; i< nbTaches; i++){
        if(taches[i]->getTitre()==nomTache){
            return i;
        }
    }
    return -1;
}

Tache& Projet::ajouterTache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
                    const Horaire& heureEcheance,const std::string & titre,const Duree & dur, bool preemptive, bool composite){
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


Projet::~Projet(){
    for(unsigned int i = 0 ; i < nbTaches ; i++){
        delete taches[i];
    }
    delete[]taches;
}

// accederTache
// verifierTaches
// verifierContraintesRespectees
// isPrecedence
