#include "tache.h"
#include "tachecomposite.h"
#include "tachesimplepreemptive.h"
#include "tachesimplenonpreemptive.h"
# include <typeinfo>
# include <iostream>
#include "tools.h"

Tache::Tache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
      const Horaire& heureEcheance,const std::string & titre,const Duree& dur):
    Element(titre, dateD, heureD, dateEcheance, heureEcheance,dur),tachesPrecedentes(){
}

bool Tache::isTachePrecedente(const std::string& titre) const{
    Tache* tachePrecedente = trouverTachePrecedente(titre);
    if (tachePrecedente == 0){
        return false;
    }
    else{
        return true;
    }
}

bool Tache::isTacheSuivante(const std::string& titre) const{
    Tache* tacheSuivante = trouverTacheSuivante(titre);
    if (tacheSuivante == 0){
        return false;
    }
    else{
        return true;
    }
}

Tache& Tache::getTachePrecedente(const std::string& titre){
    Tache* t=trouverTachePrecedente(titre);
    if (!t) {
        throw TacheException("Erreur : tache précédente inexistante");
    }
    return *t;
}

Tache& Tache::getTacheSuivante(const std::string& titre){
    Tache* t=trouverTacheSuivante(titre);
    if (!t) {
        throw TacheException("Erreur : tache suivante inexistante");
    }
    return *t;
}

Tache* Tache::trouverTachePrecedente(const std::string & titre)const{
    tp_const_iterator result = tachesPrecedentes.find(titre);
    if(result == tPEnd()) {
        return 0;
    }
    return result->second;
}

Tache* Tache::trouverTacheSuivante(const std::string & titre)const{
    ts_const_iterator result = tachesSuivantes.find(titre);
    if(result == tSEnd() ) {
        return 0;
    }
    return result->second;
}

void Tache::ajouterTachePrecedente(Tache & tachePrecedente, const std::string& cheminementPrecedent, const std::string& cheminementSuivant){
    if(trouverTachePrecedente(cheminementPrecedent)!=0){
        throw TacheException("Erreur : la tâche " + tachePrecedente.getTitre() + " précède déjà la tâche  "+ this->getTitre()+".");
    }
    if(tachePrecedente.trouverTachePrecedente(cheminementSuivant)!=0){
        throw TacheException("Erreur : la tâche " + tachePrecedente.getTitre() + " a pour tâche precedente la tâche "+ this->getTitre()+".");
    }
    if(cheminementPrecedent.compare(cheminementSuivant)==0){
        throw TacheException("Erreur : la tache "+cheminementSuivant+" ne peut pas se précéder elle meme.");
    }
    std::size_t found = cheminementPrecedent.find(cheminementSuivant);
    if (found!=std::string::npos){
        throw TacheException("Erreur : la tache mère "+cheminementSuivant+ " ne peut pas débuter après la fin de sa tache descendante " + cheminementPrecedent+".");
    }
    found = cheminementSuivant.find(cheminementPrecedent);
    if (found!=std::string::npos){
        throw TacheException("Erreur : la tache fille "+cheminementSuivant+" ne peut pas débuter après la fin de sa tache ascendante " + cheminementPrecedent+".");
    }
    if( ((this->getDateFin()-tachePrecedente.getDateDebut())*24*60+(this->getHoraireFin()-tachePrecedente.getHoraireDebut()))
            -int(tachePrecedente.getDuree().getDureeEnMinutes())< int(this->getDuree().getDureeEnMinutes())){
        throw TacheException("Erreur : la tâche " + this->getTitre() + " ne sera pas programmable.");
    }
    tachesPrecedentes.insert(std::pair<std::string, Tache*>(cheminementPrecedent, &tachePrecedente)); // ajout de la contrainte de précédence si cela est cohérent
}

void Tache::ajouterTacheSuivante(Tache & tacheSuivante, const std::string& cheminementPrecedent, const std::string& cheminementSuivant){
    if(trouverTacheSuivante(cheminementSuivant)!=0){
        throw TacheException("Erreur : la tâche " + this->getTitre() + " précède déjà la tâche "+ tacheSuivante.getTitre() +".");
    }
    if(tacheSuivante.trouverTacheSuivante(cheminementPrecedent)){
        throw TacheException("Erreur : la tâche " + tacheSuivante.getTitre() + " a pour tâche suivante la tâche "+ this->getTitre()+".");
    }
    if(cheminementPrecedent.compare(cheminementSuivant)==0){
        throw TacheException("Erreur : la tache "+cheminementSuivant+" ne peut pas se précéder elle meme.");
    }
    std::size_t found = cheminementPrecedent.find(cheminementSuivant);
    if (found!=std::string::npos){
        throw TacheException("Erreur : la tache mère "+cheminementSuivant+"ne peut pas débuter après la fin de sa tache descendante " + cheminementPrecedent+".");
    }
    found = cheminementSuivant.find(cheminementPrecedent);
    if (found!=std::string::npos){
        throw TacheException("Erreur : la tache fille "+cheminementSuivant+" ne peut pas débuter après la fin de sa tache ascendante " + cheminementPrecedent+".");
    }
    if( ((tacheSuivante.getDateFin()-this->getDateDebut())*24*60+(tacheSuivante.getHoraireFin()-this->getHoraireDebut()))
            -int(this->getDuree().getDureeEnMinutes())< int(tacheSuivante.getDuree().getDureeEnMinutes())){
        throw TacheException("Erreur : la tâche " + tacheSuivante.getTitre() + " ne sera pas programmable.");
    }
    tachesSuivantes.insert(std::pair<std::string, Tache*>(cheminementSuivant, &tacheSuivante)); // ajout de la contrainte de "suivance" si cela est cohérent
}

void Tache::supprimerTachePrecedente(const std::string & tachePrecedente){
    if(!trouverTachePrecedente(tachePrecedente)){
        throw TacheException("Erreur : la tâche " + tachePrecedente + " envoyée en paramètre ne précède pas la tâche courante "+ this->getTitre());
    }
    tachesPrecedentes.erase(tachePrecedente); // on supprime la contrainte de précédence
}

void Tache::supprimerTacheSuivante(const std::string & tacheSuivante){
    if(!trouverTacheSuivante(tacheSuivante)){
        throw TacheException("Erreur : la tâche " + this->getTitre() + " ne précède pas la tâche "+ tacheSuivante);
    }
    tachesSuivantes.erase(tacheSuivante); // on supprime la contrainte de "suivance"
}

bool Tache::checkProgrammationCoherente(const Date& dateProg, const Horaire& horaireProg, const Tache* tacheActuelle)const{
    const TacheComposite * tacheCompositeActuelle = 0 ;
    if(tacheActuelle==0){
        tacheCompositeActuelle =  dynamic_cast<const TacheComposite*>(this);
    }
    else{
        tacheCompositeActuelle = dynamic_cast<const TacheComposite *>(tacheActuelle);

    }
    const TacheSimplePreemptive * tacheSimplePreemptiveActuelle = 0;
    const TacheSimpleNonPreemptive * tacheSimpleNonPreemptiveActuelle = 0;
    if(tacheCompositeActuelle !=0){
        // on applique l'algo sur une tache composite
        for (TacheComposite::const_iterator it= tacheCompositeActuelle->begin(); it!=tacheCompositeActuelle->end(); it++){
            // on applique l'algo récursif sur toutes les taches filles de la tache composite actuelle
            if(!checkProgrammationCoherente(dateProg, horaireProg,it->second)){
                // si une tache précédente implique une programmation non cohérente, on retourne false
                return false;
            }
        }
        // toutes les taches composites parcourus sont cohérentes, c'est gagné pour la programmation
        return true;
    }
    if(tacheActuelle==0){
        tacheSimpleNonPreemptiveActuelle=dynamic_cast<const TacheSimpleNonPreemptive*>(this);
    }
    else{
        tacheSimpleNonPreemptiveActuelle=dynamic_cast<const TacheSimpleNonPreemptive*>(tacheActuelle);
    }
    if(tacheSimpleNonPreemptiveActuelle!=0){
        // on applique l'algo sur une tache simple non préemptive
        return tacheSimpleNonPreemptiveActuelle->isEndProgrammationOk(dateProg,horaireProg);
    }
    if(tacheActuelle==0){
        tacheSimplePreemptiveActuelle=dynamic_cast<const TacheSimplePreemptive*>(this);
    }
    else{
        tacheSimplePreemptiveActuelle= dynamic_cast<const TacheSimplePreemptive*>(tacheActuelle);
    }

    if(tacheSimplePreemptiveActuelle!=0){
        // on applique l'algo sur une tache simple préemptive
        return tacheSimplePreemptiveActuelle->isEndProgrammationOk(dateProg,horaireProg);
    }
    else{
        // ce cas n'est pas censé arriver vu notre architecture
        throw TacheException("Erreur : un problème subsiste dans l'application");
        return false; // pour faire plaisir au compilateur
    }
}

void Tache::exportTo(QXmlStreamWriter& stream) {
    Element::exportTo(stream);
    stream.writeStartElement("ListePrecedents");
    for(tp_iterator it=tPBegin(); it!=tPEnd(); ++it){
        stream.writeTextElement("Precedent", toQString(it->first));
    }
    stream.writeEndElement();
}

Tache::~Tache(){
    for(ts_iterator it = tSBegin(); it != tSEnd() ; ++it){
        // parcours des taches suivantes
        for(tp_iterator it2 = it->second->tPBegin() ; it2 != it->second->tPEnd() ; ++it2){
            // parcours des taches précédentes de chacune des taches suivantes
            if(it2->second == this){
                // si la tache que l'on consulte est la meme que la tache courante,
                // on supprime la contrainte
                it->second->tachesPrecedentes.erase(it2);
            }
        }
    }
    for(ts_iterator it = tPBegin(); it != tPEnd() ; ++it){
        // parcours des taches précédentes
        for(tp_iterator it2 = it->second->tSBegin() ; it2 != it->second->tSEnd() ; ++it2){
            // parcours des taches suivantes de chacune des taches précédentes
            if(it2->second == this){
                // si la tache que l'on consulte est la meme que la tache courante,
                // on supprime la contrainte
                it->second->tachesSuivantes.erase(it2);
            }
        }
    }
}

