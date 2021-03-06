# include "tachecomposite.h"
# include "tachecompositeexception.h"
# include "tachesimplepreemptive.h"
# include "tachesimplepreemptiveexception.h"
# include "tachesimplenonpreemptiveexception.h"
# include "tachesimplenonpreemptive.h"

TacheComposite::TacheComposite(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
      const Horaire& heureEcheance,const std::string & titre):
    Manager<Tache>(),Tache(dateD, heureD, dateEcheance,heureEcheance,
          titre){
}

Tache* TacheComposite::trouverSsTache(const std::string& nomTache)const{
    return getItem(nomTache);
}

void TacheComposite::ajouterSsTache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
                    const Horaire& heureEcheance,const std::string & titre,bool preemptive, bool composite, const Duree & dur){
    if(preemptive && composite){
        // ce cas n'est pas censé arriver
        throw TacheCompositeException("Erreur : on ne peut pas créer de tâche composite et preemptive");
    }
    if (trouverSsTache(titre)){
        // la tâche simple a ajouté existe déjà
        throw TacheCompositeException("Erreur : TacheSimple deja existante");
    }
    Tache* newTache = 0;
    if(preemptive && !composite){
        // on doit créer une tâche simple préemptive
        try{
            newTache = new TacheSimplePreemptive(dateD,heureD, dateEcheance, heureEcheance,
                                                 titre,dur);
        }catch (TacheSimplePreemptiveException& e){
            delete newTache;
            throw TacheCompositeException("Erreur : la tache simple préemptive n'a pas pu etre crée.");
        }
    }
    else if(!preemptive && !composite){
        try{
            newTache = new TacheSimpleNonPreemptive(dateD,heureD, dateEcheance, heureEcheance,
                                             titre,dur);
        }catch (TacheSimpleNonPreemptiveException& e){
            delete newTache;
            throw TacheCompositeException("Erreur : la tache possède une durée supérieur à 12 heures");
        }
    }
    else{
        newTache = new TacheComposite(dateD,heureD, dateEcheance, heureEcheance,
                                             titre);
    }
    if(!addItem(titre,newTache)){
        delete newTache;
        throw TacheCompositeException("Erreur : nous n'avons pas réussi à ajouter la tâche à tâche composite");
    }
}

Tache& TacheComposite::getSsTache(const std::string& titre){
    Tache* t=trouverSsTache(titre);
    if (!t) {
        throw TacheCompositeException("Erreur : tache inexistante");
    }
    return *t;
}

const Tache& TacheComposite::getSsTache(const std::string& titre)const{
    return const_cast<TacheComposite*>(this)->getSsTache(titre);
}

void TacheComposite::supprimerSsTache(const std::string& titre){
    if(!trouverSsTache(titre)){
        throw TacheCompositeException("Erreur : la tâche envoyée en paramètre n'est pas une sous tâche de la tâche composite actuelle");
    }
    Duree dureeTacheASupprimer = trouverSsTache(titre)->getDuree();
    eraseItem(titre);
    this->setDuree(this->getDuree().getDureeEnMinutes()-dureeTacheASupprimer.getDureeEnMinutes()); // mise à jour de la durée de la tâche composite
}

void TacheComposite::exportTo(QXmlStreamWriter& stream) {
    stream.writeStartElement("TacheComposite");
    Tache::exportTo(stream);
    stream.writeStartElement("ListeTaches");
    Manager::exportTo(stream);
    stream.writeEndElement();
    stream.writeEndElement();
}

void TacheComposite::exportProgrammations(QXmlStreamWriter& stream) {
    for(iterator it=begin(); it!=end(); ++it){
        (*it->second).exportProgrammations(stream);
    }
}




