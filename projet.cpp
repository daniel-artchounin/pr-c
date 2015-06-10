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
    items.erase(titre);
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
    // vérification si la tâche n'est pas
    if(dateF< dateD || (dateF==dateD && heureF < heureD )){
        return false;
    }
    if(((dateF-dateD)*24*60 + (heureF-heureD)) < int(dur.getDureeEnMinutes())){
        return false;
    }
    if(nbTaches == 0){
        if (trouverTache(titre)){
            throw ProjetException("Erreur : tache deja existante");
            return false;
        }
    }
    if( (dateD < dateDebut)
            || (dateF > dateFin)
            ||( (dateD == dateDebut) && (heureD < horaireDebut) )
            ||( (dateF == dateFin) && (heureF > horaireFin) )  ){
        return false;
    }
    if(  ( ( (getDateFin()-getDateDebut())*24*60 + (getHoraireFin()-getHoraireDebut()) ) - int(getDuree().getDureeEnMinutes()) ) < int(dur.getDureeEnMinutes())  ) {
        return false; // la duree de la tâche est supérieur à la durée libre du projet
    }
    Tache* tacheActuelle = 0;
    TacheComposite* tacheCompositeActuelle = 0;
    for(unsigned int i = 0; i < nbTaches; i++){
        if(i==0){
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
        if( (dateD < tacheCompositeActuelle->getDateDebut()) || (dateF > tacheCompositeActuelle->getDateFin())
                ||( (dateD == tacheCompositeActuelle->getDateDebut()) && (heureD < tacheCompositeActuelle->getHoraireDebut()) )
                ||( (dateF == tacheCompositeActuelle->getDateFin()) && (heureF > tacheCompositeActuelle->getHoraireFin()) )   ){
            return false;
        }
        if( ( (nbTaches-1) == i) && ( ( ( (tacheCompositeActuelle->getDateFin()-tacheCompositeActuelle->getDateDebut())*24*60 +
                                          (tacheCompositeActuelle->getHoraireFin()-tacheCompositeActuelle->getHoraireDebut()) ) -
                                        int(tacheCompositeActuelle->getDuree().getDureeEnMinutes()) ) < int(dur.getDureeEnMinutes()) ) ){
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
    /*std::cout<<"affichage :"<<std::endl;
    std::cout<<nbTaches1<<std::endl;
    std::cout<<nbTaches2<<std::endl;
    std::cout<<nomTache1<<std::endl;
    std::cout<<nomTache2<<std::endl;*/
    Tache& tache1 = accederTache(nomsTachesComposites1, nbTaches1, nomTache1);
    Tache& tache2 = accederTache(nomsTachesComposites2, nbTaches2, nomTache2);
    std::string chemin1 = genererChemin(nomsTachesComposites1, nbTaches1, nomTache1);
    std::string chemin2 = genererChemin(nomsTachesComposites2, nbTaches2, nomTache2);
    // std::cout << chemin1<<std::endl;
    // std::cout << chemin2<<std::endl;
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

void Projet::loadListePrecedents(QXmlStreamReader &xml, std::string * arr, int longueur, std::string titre) {
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "ListePrecedents")) {
        xml.readNextStartElement();
        if(xml.name() == "Precedent") {
            xml.readNext();
            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Precedent")) {
                std::string chemin= toString(xml.text().toString());
                std::string delimiter = "/";
                int nbPrecedents=std::count(chemin.begin(), chemin.end(), '/');
                std::string precedents[nbPrecedents];
                size_t pos = 0;
                int i=0;
                while ((pos = chemin.find(delimiter)) != std::string::npos) {
                    precedents[i] = chemin.substr(0, pos);
                    chemin.erase(0, pos + delimiter.length());
                    i++;
                }
                ajouterPrecedence(precedents,nbPrecedents,chemin,arr,longueur,titre);
                xml.readNext();
            }
        }
    }
}

void Projet::loadFrom(QXmlStreamReader &xml, std::vector<std::string>& vect) {
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
                        loadListePrecedents(xml,arr,(int)(vect.size()),titre);
                    }
                }
                xml.readNext();
            }
        }
    }
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
