#include "tache.h"
#include "tachecomposite.h"
#include "tachesimplepreemptive.h"
#include "tachesimplenonpreemptive.h"

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

void Tache::ajouterTachePrecedente(Tache & tachePrecedente){
    if(trouverTachePrecedente(tachePrecedente.getTitre())){
        throw TacheException("Erreur : la tâche " + tachePrecedente.getTitre() + " envoyée en paramètre précède déjà la tâche courante "+ this->getTitre());
    }
    if(tachePrecedente.trouverTachePrecedente(tachePrecedente.getTitre())){
        throw TacheException("Erreur : la tâche " + tachePrecedente.getTitre() + " envoyée en paramètre a pour tâche precedente la tâche courante "+ this->getTitre());
    }
    if( ((this->getDateFin()-tachePrecedente.getDateDebut())*24*60+(this->getHoraireFin()-tachePrecedente.getHoraireDebut()))
            -tachePrecedente.getDuree().getDureeEnMinutes()< this->getDuree().getDureeEnMinutes()){
        throw TacheException("Erreur : la tâche " + tachePrecedente.getTitre() + " envoyée en paramètre ne sera pas programmable");
    }
    tachesPrecedentes.insert(std::pair<std::string, Tache*>(tachePrecedente.getTitre(), &tachePrecedente));
}

void Tache::supprimerTachesPrecedente(const std::string & tachePrecedente){
    if(!trouverTachePrecedente(tachePrecedente)){
        throw TacheException("Erreur : la tâche " + tachePrecedente + " envoyée en paramètre ne précède pas la tâche courante "+ this->getTitre());
    }
    tachesPrecedentes.erase(tachePrecedente);
}

bool Tache::checkProgrammationCoherente(const Date& dateProg, const Horaire& horaireProg, const Tache* tacheActuelle)const{
    TacheComposite * tacheCompositeActuelle = 0 ;
    if(!tacheActuelle){
        tacheCompositeActuelle =  dynamic_cast<TacheComposite*>(const_cast<Tache*>(this));
    }
    else{
        tacheCompositeActuelle = dynamic_cast<TacheComposite *>(const_cast<Tache*>(tacheActuelle));

    }
    TacheSimplePreemptive * tacheSimplePreemptiveActuelle = 0;
    TacheSimpleNonPreemptive * tacheSimpleNonPreemptiveActuelle = 0;
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
    else if(!(tacheSimpleNonPreemptiveActuelle=dynamic_cast< TacheSimpleNonPreemptive *>(const_cast<Tache*>(tacheActuelle)))){
        // on applique l'algo sur une tache simple non préemptive
        return tacheSimpleNonPreemptiveActuelle->isEndProgrammationOk(dateProg,horaireProg);
    }
    else if(!(tacheSimplePreemptiveActuelle= dynamic_cast<TacheSimplePreemptive *>(const_cast<Tache*>(tacheActuelle)) ) ){
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
    stream.writeStartElement("Precedents");
    for(tp_iterator it=tPBegin(); it!=tPEnd(); ++it){
        (*it->second).exportTo(stream);
    }
    stream.writeEndElement();
}


