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

Tache* Tache::trouverTachePrecedente(const std::string & titre)const{
    tp_const_iterator result = tachesPrecedentes.find(titre);
    if(result == tPEnd()) {
        return 0;
    }
    return result->second;
}

void Tache::ajouterTachePrecedente(Tache & tachePrecedente, const std::string& cheminementPrecedent, const std::string& cheminementSuivant){
    if(trouverTachePrecedente(cheminementPrecedent)){
        throw TacheException("Erreur : la tâche " + tachePrecedente.getTitre() + " envoyée en paramètre précède déjà la tâche courante "+ this->getTitre());
    }
    if(tachePrecedente.trouverTachePrecedente(cheminementSuivant)){
        throw TacheException("Erreur : la tâche " + tachePrecedente.getTitre() + " envoyée en paramètre a pour tâche precedente la tâche courante "+ this->getTitre());
    }
    if( ((this->getDateFin()-tachePrecedente.getDateDebut())*24*60+(this->getHoraireFin()-tachePrecedente.getHoraireDebut()))
            -tachePrecedente.getDuree().getDureeEnMinutes()< this->getDuree().getDureeEnMinutes()){
        throw TacheException("Erreur : la tâche " + tachePrecedente.getTitre() + " envoyée en paramètre ne sera pas programmable");
    }
    tachesPrecedentes.insert(std::pair<std::string, Tache*>(cheminementPrecedent, &tachePrecedente));
}

void Tache::supprimerTachesPrecedente(const std::string & tachePrecedente){
    if(!trouverTachePrecedente(tachePrecedente)){
        throw TacheException("Erreur : la tâche " + tachePrecedente + " envoyée en paramètre ne précède pas la tâche courante "+ this->getTitre());
    }
    tachesPrecedentes.erase(tachePrecedente);
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
        // ce cas n'est pas censé arrivé vu notre architecture
        throw TacheException("checkProgrammationCoherente : un problème subsiste dans l'application");
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


