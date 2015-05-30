#include "tachecomposite.h"
#include "tachecompositeexception.h"
#include "tachesimplepreemptive.h"
#include "tachesimplenonpreemptiveexception.h"
#include "tachesimplenonpreemptive.h"

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
        throw TacheCompositeException("erreur : On ne peut pas créer de tâche composite et preemptive");
    }
    if (trouverSsTache(titre))
        throw TacheCompositeException("erreur : TacheSimple deja existante");
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
            throw TacheCompositeException("La tache possède une durée supérieur à 12 heures");
        }
    }
    else{
        newTache = new TacheComposite(dateD,heureD, dateEcheance, heureEcheance,
                                             titre);
    }
    if(!addItem(titre,newTache)){
        delete newTache;
        throw TacheCompositeException("erreur : Nous n'avons pas réussi à ajouter la tâche à tâche composite");
    }
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
    if(!trouverSsTache(titre)){
        throw TacheCompositeException("Erreur : la tâche envoyée en paramètre ne précède pas la tâche actuelle");
    }
    items.erase(titre);
}

void TacheComposite::exportTo(QXmlStreamWriter& stream) {
    stream.writeStartElement("TacheComposite");
    Tache::exportTo(stream);
    for(iterator it=begin(); it!=end(); ++it){
        (*it->second).exportTo(stream);
    }
    stream.writeEndElement();
}




