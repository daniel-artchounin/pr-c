#include "tache.h"
# include "tacheexception.h"

Tache::Tache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
      const Horaire& heureEcheance,const std::string & titre):
    Element(dateD,heureD, titre, dateEcheance, heureEcheance),
    tachesPrecedentes(0), nbTachesPrecedentes(0), nbTachesPrecedentesMax(0){
}

Tache** Tache::getTachesPrecedentes()const{
    return tachesPrecedentes;
}

int Tache::getNbTachesPrecedentes() const{
    return nbTachesPrecedentes;
}

int Tache::getNbTachesPrecedentesMax() const{
    return nbTachesPrecedentesMax;
}

bool Tache::finTachesPrecedentes() const{
    for(unsigned int i = 0; i < nbTachesPrecedentes; i++ ){
        if(!(tachesPrecedentes[i]->isTermine())) {
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
    for (unsigned int i = 0 ; i< nbTachesPrecedentes; i++){
        if(tachesPrecedentes[i]==&tachePotentPrecedente){
            return tachesPrecedentes[i];
        }
    }
    return 0;
}

void Tache::ajouterTachePrecedente(Tache & tachePrecedente){
    if(tachePrecedente.trouverTachePrecedente(*this)){
        throw TacheException("Erreur : la tâche envoyée en paramètre a pour tâche precedente la tâche courante");
    }
    if (nbTachesPrecedentes==nbTachesPrecedentesMax){
        Tache** newtab=new Tache*[nbTachesPrecedentesMax+10];
        for(unsigned int i=0; i<nbTachesPrecedentes; i++)
            newtab[i]=tachesPrecedentes[i];
        nbTachesPrecedentesMax+=10;
        Tache** old = tachesPrecedentes;
        tachesPrecedentes = newtab;
        delete[] old;
    }
    tachesPrecedentes[nbTachesPrecedentes++]=&tachePrecedente;
}
void Tache::supprimerTachesPrecedente(const Tache & tachePrecedente){
    for (unsigned int i = 0; i < nbTachesPrecedentesMax ; i++ ){
        if (tachesPrecedentes[i] == &tachePrecedente) {
            tachesPrecedentes[i]= tachesPrecedentes[nbTachesPrecedentes];
            nbTachesPrecedentes--;
        }
    }
}
