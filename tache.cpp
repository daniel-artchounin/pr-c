#include "tache.h"

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


bool Tache::finTachesPrecedentes() const{
    for(unsigned int i = 0; i < nbTachesPrecedentes; i++ ){
        if(!(tachesPrecedentes[i]->isTermine())) {
            return false;
        }
    }
    return true;
}

bool Tache::isTachePrecedente(const Tache& tachePotentPrecedente) const{
    for(unsigned int i = 0; i < nbTachesPrecedentes; i++ ){
        if(tachesPrecedentes[i]== &tachePotentPrecedente){
            return true;
        }
    }
    return false;
}

void Tache::ajouterTachePrecedente(Tache & tachePrecedente){
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
