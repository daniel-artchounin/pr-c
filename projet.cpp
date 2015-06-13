#include "projet.h"
#include "tachesimplepreemptive.h"
#include "tachesimplenonpreemptive.h"
#include "tachesimplenonpreemptiveexception.h"
#include "tachecompositeexception.h"
# include <string>
#include "projetexception.h"
#include "tools.h"
#include "programmationmanager.h"
#include <algorithm>

Projet::Projet(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
               const Horaire& heureEcheance,const std::string & titre):
    Manager<Tache>(),Element(titre, dateD, heureD, dateEcheance, heureEcheance){}

Tache* Projet::trouverTache(const std::string& nomTache)const{
    return getItem(nomTache);
}

void Projet::ajouterTache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
                          const Horaire& heureEcheance,const std::string & titre,bool preemptive, bool composite, const Duree & dur){
    if(preemptive && composite){
        throw ProjetException("Erreur : on ne peut pas créer de tâche composite et preemptive");
    }
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
            throw ProjetException("Erreur : la tache possède une durée supérieur à 12 heures");
        }
        newTache = new TacheSimpleNonPreemptive(dateD,heureD, dateEcheance, heureEcheance,
                                                titre,dur);
    }
    else{
        newTache = new TacheComposite(dateD,heureD, dateEcheance, heureEcheance,
                                      titre);
    }
    if(!addItem(titre,newTache)){
        delete newTache;
        throw TacheCompositeException("Erreur : nous n'avons pas réussi à ajouter la tâche au projet");
    }
}

Tache& Projet::getTache(const std::string& titre){
    Tache* t=trouverTache(titre);
    if (!t) {
        throw ProjetException("Erreur : tache inexistante");
    }
    return *t;
}

const Tache& Projet::getTache(const std::string& titre)const{
    return const_cast<Projet*>(this)->getTache(titre);
}

void Projet::supprimerTache(const std::string& titre){
    if(!trouverTache(titre)){
        throw TacheCompositeException("Erreur : tache inexistante");
    }
    Duree dureeTacheASupprimer = trouverTache(titre)->getDuree(); // on conserve la durée de la tâche à supprimer
    eraseItem(titre);
    // items.erase(titre); // suppression
    this->setDuree(this->getDuree().getDureeEnMinutes()-dureeTacheASupprimer.getDureeEnMinutes());
}

Tache& Projet::accederTache(const std::string * nomsTachesComposites , unsigned int nbTaches,
                            const std::string& nomTache, unsigned int profondeur, const TacheComposite* tacheCourante)const{
    const TacheComposite* newTache = 0;
    if (nbTaches == 0){
        // la tâche recherchée se trouve directement à la racine du projet
        return const_cast<Projet*>(this)->getTache(nomTache);
    }
    else{
        // la tâche recherchée ne se trouve pas directement à la racine du projet
        if(profondeur == nbTaches){
            // la tâche recherchée est une sous tâche de la tâche composite actuelle
            return const_cast<TacheComposite*>(tacheCourante)->getSsTache(nomTache);
        }
        else if(profondeur == 0){
            // on cherche une tâche composite à la racine du projet
            try{
                newTache = dynamic_cast<TacheComposite*>(trouverTache(nomsTachesComposites[profondeur]));
            }
            catch(std::bad_cast& e){
                // on n'est normalement pas censé entrer ici car dynamic_cast ne génère pas d'exception pour les
                // conversions de pointeur
                throw ProjetException("Les titres de tâches données en paramètres ne sont pas des taches composites");
            }
            if(newTache == 0){
                throw ProjetException("Les titres de tâches données en paramètres ne sont pas des taches composites");
            }
            return accederTache(nomsTachesComposites, nbTaches, nomTache, profondeur+1,newTache);
        }
        else{
            // on cherche une tâche composite sous la tâche composite actuelle
            try{
                newTache = dynamic_cast<TacheComposite *>(tacheCourante->trouverSsTache(nomsTachesComposites[profondeur]));
            }
            catch(std::bad_cast &e){
                // on n'est normalement pas censé entrer ici car dynamic_cast ne génère pas d'exception pour les
                // conversions de pointeur
                throw ProjetException("Les titres de tâches données en paramètres ne sont pas des taches composites");
            }
            if(newTache == 0){
                throw ProjetException("Les titres de tâches données en paramètres ne sont pas des taches composites");
            }
            return accederTache(nomsTachesComposites,nbTaches, nomTache, profondeur+1,newTache);
        }
    }
}

bool Projet::verifierContraintesRespectees(const std::string * nomsTaches, unsigned int nbTaches, const Date& dateD
                                           ,const Horaire& heureD,const Date& dateF, const Horaire& heureF,const Duree & dur)const{
    if(dateF< dateD || (dateF==dateD && heureF < heureD )){
        // on vérifie si la disponibilité et l'échéance de la tâche en puissance sont déjà cohérentes
        return false;
    }
    if(((dateF-dateD)*24*60 + (heureF-heureD)) < int(dur.getDureeEnMinutes())){
        // on vérifie que la durée de l'intervalle entre la disponibilité et l'échéance de la tâche en puissance est supérieure ou
        // égale à sa durée
        return false;
    }
    if(nbTaches == 0){
        // si la tâche doit-être ajoutée à la racine du projet
        if (trouverTache(titre)){
            // on vérifie que la tâche n'existe pas déjà
            throw ProjetException("Erreur : tache deja existante");
            return false;
        }
    }
    if( (dateD < dateDebut)
            || (dateF > dateFin)
            ||( (dateD == dateDebut) && (heureD < horaireDebut) )
            ||( (dateF == dateFin) && (heureF > horaireFin) )  ){
        // on vérifie que l'intervalle de temps entre la disponibilité et l'échéance de la tâche en puissance
        // est inclus dans celui du projet
        return false;
    }
    if(  ( ( (getDateFin()-getDateDebut())*24*60 + (getHoraireFin()-getHoraireDebut()) ) - int(getDuree().getDureeEnMinutes()) ) < int(dur.getDureeEnMinutes())  ) {
        return false; // la duree de la tâche est supérieur à la durée libre du projet
    }
    Tache* tacheActuelle = 0;
    TacheComposite* tacheCompositeActuelle = 0;
    for(unsigned int i = 0; i < nbTaches; i++){
        if(i==0){
            // on met à jour la tâche composite à laquelle on va s'intéresser
            // cette dernière se trouve à la racine du projet
            tacheActuelle = trouverTache(nomsTaches[i]);
        }
        else{
            // on met à jour la tâche composite à laquelle on va s'intéresser
            // cette dernière ne se trouve pas à la racine du projet
            tacheActuelle = tacheCompositeActuelle->trouverSsTache(nomsTaches[i]);
        }
        if(tacheActuelle == 0){
            throw ProjetException("Erreur : tache inexistante");
        }
        try{
            tacheCompositeActuelle = dynamic_cast<TacheComposite*>(tacheActuelle);
        }
        catch(std::bad_cast& e){
            // on n'est normalement pas censé entrer ici car dynamic_cast ne génère pas d'exception pour les
            // conversions de pointeur
            throw ProjetException("Erreur : les titres de tâches données en paramètres ne sont pas des taches composites");
        }
        if(tacheCompositeActuelle == 0){
            throw ProjetException("Erreur : les titres de tâches données en paramètres ne sont pas des taches composites");
        }
        if( (dateD < tacheCompositeActuelle->getDateDebut()) || (dateF > tacheCompositeActuelle->getDateFin())
                ||( (dateD == tacheCompositeActuelle->getDateDebut()) && (heureD < tacheCompositeActuelle->getHoraireDebut()) )
                ||( (dateF == tacheCompositeActuelle->getDateFin()) && (heureF > tacheCompositeActuelle->getHoraireFin()) )   ){
            // on vérifie que l'intervalle de temps entre la disponibilité et l'échéance de la tâche en puissance
            // est inclus dans celui de la tâche composite actuelle
            return false;
        }
        if( ( ( (tacheCompositeActuelle->getDateFin()-tacheCompositeActuelle->getDateDebut())*24*60 +
                                          (tacheCompositeActuelle->getHoraireFin()-tacheCompositeActuelle->getHoraireDebut()) ) -
                                        int(tacheCompositeActuelle->getDuree().getDureeEnMinutes()) ) < int(dur.getDureeEnMinutes()) ){
            return false; // la duree de la tâche est supérieur à la durée libre de la tâche composite
        }
    }
    return true;

}

void Projet::creerAjouterTache(const std::string * nomsTaches, unsigned int nbTaches, const Date& dateD
                               ,const Horaire& heureD,const Date& dateF, const Horaire& heureF,
                               const std::string& titre, bool preemptive, bool composite,const Duree & dur){
    if(!verifierContraintesRespectees(nomsTaches,nbTaches, dateD,heureD, dateF, heureF, dur)){
        throw ProjetException("Erreur : création de la tâche " + titre + " impossible car les contraintes ne sont pas respectées");
    }
    if(!preemptive && !(dur <  Duree(12,00))){
            throw ProjetException("Erreur : la durée tansmise en paramètres n'est pas valide (elle est supérieure ou égale à 12 h 00)");
    }
    Tache* tacheActuelle = 0;
    TacheComposite* tacheCompositeActuelle = 0;
    if(nbTaches==0){
        addDuree(dur); // on ajoute la durée de la tache au projet
        ajouterTache(dateD,heureD,dateF, heureF, titre, preemptive, composite, dur);
    }
    else {
        for(unsigned int i = 0; i < nbTaches; i++){
            if(i==0){
                // ajoute la durée au projet
                addDuree(dur);
                tacheActuelle = trouverTache(nomsTaches[i]);
            }
            else{
                tacheActuelle = tacheCompositeActuelle->trouverSsTache(nomsTaches[i]);
            }
            if(tacheActuelle == 0){
                throw ProjetException("Erreur : tache inexistante");
            }
            try{
                tacheCompositeActuelle = dynamic_cast<TacheComposite*>(tacheActuelle);
            }
            catch(std::bad_cast& e){
                // on n'est normalement pas censé entrer ici car dynamic_cast ne génère pas d'exception pour les
                // conversions de pointeur
                throw ProjetException("Erreur : les titres de tâches données en paramètres ne sont pas des taches composites");
            }
            if(tacheCompositeActuelle == 0){
                throw ProjetException("Erreur : les titres de tâches données en paramètres ne sont pas des taches composites");
            }
            tacheCompositeActuelle->addDuree(dur);
        }
        tacheCompositeActuelle->ajouterSsTache(dateD,heureD,dateF, heureF, titre, preemptive, composite, dur);

    }
}

void Projet::ajouterPrecedence(const std::string * nomsTachesComposites1, unsigned int nbTaches1,const std::string& nomTache1,
                               const std::string * nomsTachesComposites2, unsigned int nbTaches2,const std::string& nomTache2){
    Tache& tache1 = accederTache(nomsTachesComposites1, nbTaches1, nomTache1);
    Tache& tache2 = accederTache(nomsTachesComposites2, nbTaches2, nomTache2);
    std::string chemin1 = genererChemin(nomsTachesComposites1, nbTaches1, nomTache1);
    std::string chemin2 = genererChemin(nomsTachesComposites2, nbTaches2, nomTache2);
    tache2.ajouterTachePrecedente(tache1, chemin1, chemin2);
    tache1.ajouterTacheSuivante(tache2, chemin1, chemin2);
}

void Projet::supprimerPrecedence(const std::string * nomsTachesComposites1, unsigned int nbTaches1,const std::string& nomTache1,
                                 const std::string * nomsTachesComposites2, unsigned int nbTaches2,const std::string& nomTache2){
    Tache& tache1 = accederTache(nomsTachesComposites1, nbTaches1, nomTache1);
    Tache& tache2 = accederTache(nomsTachesComposites2, nbTaches2, nomTache2);
    std::string chemin1 = genererChemin(nomsTachesComposites1, nbTaches1, nomTache1);
    std::string chemin2 = genererChemin(nomsTachesComposites2, nbTaches2, nomTache2);
    tache2.supprimerTachePrecedente(chemin1);
    tache1.supprimerTacheSuivante(chemin2);
}

void Projet::exportTo(QXmlStreamWriter& stream) {
    stream.writeStartElement("Projet");
    Element::exportTo(stream);
    stream.writeStartElement("ListeTaches");
    Manager::exportTo(stream);
    stream.writeEndElement();
    stream.writeEndElement();
}

void Projet::exportProgrammations(QXmlStreamWriter& stream) {
    stream.writeStartElement("Programmations");
    for(iterator it=begin(); it!=end(); ++it){
        (*it->second).exportProgrammations(stream);
    }
    stream.writeEndElement();
}

std::vector<std::vector<std::string> > Projet::loadListePrecedents(QXmlStreamReader &xml, std::string * arr, int longueur, std::string titre) {
    std::vector<std::vector<std::string> > contraintesPrecedences;
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "ListePrecedents")) {
        xml.readNextStartElement();
        if(xml.name() == "Precedent") {
            xml.readNext();
            std::vector<std::string> contraintes;
            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Precedent")) {
                contraintes.push_back(toString(xml.text().toString()));
                std::string combine;
                for(int i=0; i<longueur; i++) {
                    combine.append(arr[i]+"/");
                }
                combine.append(titre);
                contraintes.push_back(combine);
                contraintesPrecedences.push_back(contraintes);
                xml.readNext();
            }
        }
    }
    return contraintesPrecedences;
}

void Projet::ajouterListePrecedences(std::vector<std::vector<std::string> > contraintesPrecedences) {
    for(std::vector<std::vector<std::string> >::iterator it=contraintesPrecedences.begin(); it!=contraintesPrecedences.end(); ++it) {
        std::vector<std::string> vect= *it;
        std::string cheminPredecesseur= vect[0];
        std::string cheminSuccesseur= vect[1];
        std::string delimiter = "/";
        int tailleCheminPredecesseur=std::count(cheminPredecesseur.begin(), cheminPredecesseur.end(), '/');
        int tailleCheminSuccesseur=std::count(cheminSuccesseur.begin(), cheminSuccesseur.end(), '/');
        std::string parentsPredecesseur[tailleCheminPredecesseur];
        std::string parentsSuccesseur[tailleCheminPredecesseur];
        size_t pos = 0;
        int i=0;
        while ((pos = cheminPredecesseur.find(delimiter)) != std::string::npos) {
            parentsPredecesseur[i] = cheminPredecesseur.substr(0, pos);
            cheminPredecesseur.erase(0, pos + delimiter.length());
            i++;
        }
        pos=0;
        i=0;
        while ((pos = cheminSuccesseur.find(delimiter)) != std::string::npos) {
            parentsSuccesseur[i] = cheminSuccesseur.substr(0, pos);
            cheminSuccesseur.erase(0, pos + delimiter.length());
            i++;
        }
        ajouterPrecedence(parentsPredecesseur,tailleCheminPredecesseur,cheminPredecesseur,parentsSuccesseur,tailleCheminSuccesseur,cheminSuccesseur);
    }
}

void Projet::loadFrom(QXmlStreamReader &xml, std::vector<std::string>& vect) {
    std::vector<std::vector<std::string> > contraintesPrecedences;
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "ListeTaches")) {
        xml.readNextStartElement();
        bool composite = false;
        bool preemptive = false;
        if(xml.name() == "TacheComposite") {
            composite = true;
        }
        if(xml.name() == "TachePreemptive") {
            preemptive = true;
        }
        if(xml.name() == "TacheComposite" || xml.name() == "TachePreemptive" || xml.name() == "TacheSimpleNonPreemptive") {
            std::string titre;
            std::string dateDebut;
            std::string horaireDebut;
            std::string dateFin;
            std::string horaireFin;
            std::string duree;
            xml.readNext();
            while(!(xml.tokenType() == QXmlStreamReader::EndElement && (xml.name() == "TacheComposite" || xml.name() == "TachePreemptive" || xml.name() == "TacheSimpleNonPreemptive"))) {
                if(xml.tokenType() == QXmlStreamReader::StartElement) {
                    if(xml.name() == "titre") {
                        xml.readNext();
                        titre=toString(xml.text().toString());
                    }else if(xml.name() == "dateDebut") {
                        xml.readNext();
                        dateDebut=toString(xml.text().toString());
                    }else if(xml.name() == "horaireDebut") {
                        xml.readNext();
                        horaireDebut=toString(xml.text().toString());
                    }else if(xml.name() == "dateFin") {
                        xml.readNext();
                        dateFin=toString(xml.text().toString());
                    }else if(xml.name() == "horaireFin") {
                        xml.readNext();
                        horaireFin=toString(xml.text().toString());
                    }else if(xml.name() == "duree") {
                        xml.readNext();
                        duree=toString(xml.text().toString());
                    }else if(xml.name() == "ListeTaches") {
                        xml.readNext();
                        vect.push_back(titre);
                        loadFrom(xml,vect);
                    }else if(xml.name() == "ListeProgrammations") {
                        xml.readNext();
                        std::string arr[(int)(vect.size())];
                        std::copy(vect.begin(), vect.end(), arr);

                        ProgrammationManager::getInstance().loadListeProgrammations(xml, accederTache(arr,(int)vect.size(),titre),preemptive);
                    }else if(xml.name() == "ListePrecedents") {
                        xml.readNext();
                        std::string arr[(int)(vect.size())];
                        std::copy(vect.begin(), vect.end(), arr);
                        try {
                            if(composite) {
                                creerAjouterTache(arr,(int)vect.size(),Date(dateDebut),Horaire(horaireDebut),Date(dateFin),Horaire(horaireFin),titre,preemptive,composite);
                            } else {
                                creerAjouterTache(arr,(int)vect.size(),Date(dateDebut),Horaire(horaireDebut),Date(dateFin),Horaire(horaireFin),titre,preemptive,composite,Duree(duree));
                            }
                        }catch(TacheCompositeException tce) {

                        }catch(ProjetException pe) {

                        }
                        std::vector<std::vector<std::string> > contraintes = loadListePrecedents(xml,arr,(int)(vect.size()),titre);;
                        contraintesPrecedences.insert(contraintesPrecedences.end(), contraintes.begin(), contraintes.end());
                    }
                }
                xml.readNext();
            }
        }
    }
    ajouterListePrecedences(contraintesPrecedences);
    if(!vect.empty()) {
        vect.pop_back();
    }
}

std::string Projet::genererChemin(const std::string * nomsTachesComposites, unsigned int nbTaches,const std::string& nomTache){
    std::string chemin = "";
    for (unsigned int i=0; i<nbTaches; i++){
        chemin += (nomsTachesComposites[i]+'/');
    }
    chemin += nomTache;
    return chemin;
}

Duree Projet::supprimerTacheChemin(const std::string * nomsTachesComposites, unsigned int nbTaches,const std::string& nomTache,
                          unsigned int profondeur, const TacheComposite* tacheCourante){
    const TacheComposite* newTache = 0;
    if(nbTaches == 0){
        // la tâche à supprimer se trouve à la racine du projet
        Duree dureeTacheASupprimer = trouverTache(nomTache)->getDuree();
        supprimerTache(nomTache);
        return dureeTacheASupprimer;
    }
    else{
        // la tâche recherchée ne se trouve pas directement à la racine du projet
        if(profondeur == nbTaches){
            // la tâche recherchée est une sous tâche de la tâche composite actuelle
            Duree dureeTacheASupprimer = const_cast<TacheComposite*>(tacheCourante)->getSsTache(nomTache).getDuree();
            const_cast<TacheComposite*>(tacheCourante)->supprimerSsTache(nomTache);
            return dureeTacheASupprimer;
        }
        else if(profondeur == 0){
            // on cherche une tâche composite à la racine du projet
            try{
                newTache = dynamic_cast<TacheComposite*>(trouverTache(nomsTachesComposites[profondeur]));
            }
            catch(std::bad_cast& e){
                // on n'est normalement pas censé entrer ici car dynamic_cast ne génère pas d'exception pour les
                // conversions de pointeur
                throw ProjetException("Erreur : Les titres de tâches données en paramètres ne sont pas des taches composites");
            }
            if(newTache == 0){
                throw ProjetException("Erreur : Les titres de tâches données en paramètres ne sont pas des taches composites");
            }
            Duree dureeTacheASupprimer = supprimerTacheChemin(nomsTachesComposites, nbTaches, nomTache, profondeur+1,newTache); // appel récursif
            this->setDuree(this->getDuree().getDureeEnMinutes()-dureeTacheASupprimer.getDureeEnMinutes()); // maj de la durée du projet
            return dureeTacheASupprimer;
        }
        else{
            // on cherche une tâche composite sous la tâche composite actuelle
            try{
                newTache = dynamic_cast<TacheComposite *>(tacheCourante->trouverSsTache(nomsTachesComposites[profondeur]));
            }
            catch(std::bad_cast &e){
                // on n'est normalement pas censé entrer ici car dynamic_cast ne génère pas d'exception pour les
                // conversions de pointeur
                throw ProjetException("Erreur : Les titres de tâches données en paramètres ne sont pas des taches composites");
            }
            if(newTache == 0){
                throw ProjetException("Erreur : Les titres de tâches données en paramètres ne sont pas des taches composites");
            }
            Duree dureeTacheASupprimer = supprimerTacheChemin(nomsTachesComposites, nbTaches, nomTache, profondeur+1,newTache); // appel récursif
             const_cast<TacheComposite*>(tacheCourante)->setDuree(tacheCourante->getDuree().getDureeEnMinutes()-dureeTacheASupprimer.getDureeEnMinutes()); // maj de la durée de la TC
            return dureeTacheASupprimer;
        }
    }
}
