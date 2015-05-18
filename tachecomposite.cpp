#include "tachecomposite.h"

void TacheComposite::addItem(Tache* t){
    if (nbSsTaches==nbSsTachesMax){
        Tache** newtab=new Tache*[nbSsTachesMax+10];
        for(unsigned int i=0; i<nbSsTaches; i++)
            newtab[i]=ssTaches[i];
        nbSsTachesMax+=10;
        Tache** old=ssTaches;
        ssTaches=newtab;
        delete[] old;
    }
    ssTaches[nbSsTaches++]=t;
}

TacheComposite::TacheComposite(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
      const Horaire& heureEcheance,const std::string & titre):
    Tache(dateD, heureD, dateEcheance,heureEcheance,
          titre), ssTaches(0), nbSsTaches(0), nbSsTachesMax(0){
}
Tache** TacheComposite::getSsTaches() const{
    return ssTaches;
}
int TacheComposite::getnbSsTaches(){
    return nbSsTaches;
}
int TacheComposite::getnbSsTachesMax(){
    return nbSsTachesMax;
}
Tache* TacheComposite::trouverSsTache(const std::string& nomTache)const{
    for (unsigned int i = 0 ; i< nbSsTaches; i++){
        if(ssTaches[i]->getTitre()==nomTache){
            return ssTaches[i];
        }
    }
    return 0;
}
int TacheComposite::trouverIndiceSsTache(const std::string& nomTache)const{
    for (unsigned int i = 0 ; i< nbSsTaches; i++){
        if(ssTaches[i]->getTitre()==nomTache){
            return i;
        }
    }
    return -1;
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
        newTache = new TacheSimpleNonPreemptive(dateD,heureD, dateEcheance, heureEcheance,
                                             titre,dur);
    }
    addItem(newTache);
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
    int i =trouverIndiceSsTache(titre);
    if (i == -1){
        throw TacheCompositeException("erreur : tache inexistante");
    }
    Tache * t = ssTaches[i];
    if(nbSsTaches > 1){
        ssTaches[i]=ssTaches[nbSsTaches-1];
    }
    delete t;
    nbSsTaches--;
}

bool TacheComposite::isTermine()const{
    for (unsigned int i = 0 ; i< nbSsTaches; i++){
        if(!ssTaches[i]->isTermine()){
            return false;
        }
    }
    return true;
}

TacheComposite::~TacheComposite(){
    for(unsigned int i = 0 ; i < nbSsTaches ; i++){
        delete ssTaches[i];
    }
    delete[]ssTaches;
}
