#include "programmationmanager.h"
#include "programmationmanagerexception.h"
#include "programmationevenement.h"
#include "programmationtachesimple.h"
#include "programmationtachesimplenonpreemptive.h"
#include "programmationtachesimplepreemptive.h"
#include <typeinfo>
#include <iostream>
#include "tools.h"

//design pattern singleton
ProgrammationManager * ProgrammationManager::instance=0; //initialisation à null, pour la première vérification

ProgrammationManager& ProgrammationManager::getInstance() {
    //si l'instance interne n'est pas encore créé, on doit le faire
    if(instance == 0){
        instance = new ProgrammationManager();
    }
    return *instance;
}

void ProgrammationManager::libererInstance() {
    if(instance != 0){
        delete instance;
        instance = 0;
    }
}


bool ProgrammationManager::inclus(const Date& dateProg, const Horaire& horaireProg, const Date& dateFin, const Horaire& horaireFin, const Date& date, const Horaire& horaire) const {
    return (dateProg<date || (dateProg==date && horaireProg<=horaire)) && (date<dateFin || (date==dateFin && horaire<=horaireFin));
}

bool ProgrammationManager::hasIntersection(const Date& dateProg, const Horaire& horaireProg, const Date& dateFin, const Horaire& horaireFin, const Date& newDate, const Horaire& newHoraire, const Duree& newDuree) const{
    return inclus(dateProg, horaireProg, dateFin, horaireFin, newDate, newHoraire) || inclus(newDate, newHoraire, newDate.addDuree(newDuree), newHoraire.addDuree(newDuree), dateProg, horaireProg);
}

bool ProgrammationManager::isValid(const Date& date, const Horaire& horaire, const Duree& duree) {
    if(items.find(getKeyFrom(date, horaire))!=end()) {
        return false;
    }
    for(iterator it=begin(); it!=end(); it++) {
        Programmation& prog = *it->second;
        if(hasIntersection(prog.getDateProgrammation(), prog.getHoraireProgrammation(), prog.getDateFin(), prog.getHoraireFin(), date, horaire, duree)) {
            return false;
        }
    }
    return true;
}

std::string ProgrammationManager::getKeyFrom(const Date& date, const Horaire& horaire) {
    return date.formatAAAAMMJJ()+horaire.formatHHMM();
}

ProgrammationEvenement& ProgrammationManager::addProgrammationEvenement(const Date& dateProg, const Horaire& horaireProg, const Duree& duree) {
    if(!isValid(dateProg, horaireProg, duree)) {
        throw ProgrammationManagerException("Erreur, ProgrammationManager, addProgrammationEvenement, Programmation incompatible avec une programmation existante");
    }
    ProgrammationEvenement* programmation = new ProgrammationEvenement(dateProg, horaireProg, duree);
    Manager::addItem(getKeyFrom(dateProg, horaireProg), programmation);
    return *programmation;
}

Programmation& ProgrammationManager::getProgrammation(const Date& dateProg, const Horaire& horaireProg) {
    Programmation* programmation=getItem(getKeyFrom(dateProg, horaireProg));
    if (!programmation) throw ProgrammationManagerException("erreur, ProgrammationManager, getProgrammation, Programmation inexistante");
    return *programmation;
}

const Programmation& ProgrammationManager::getProgrammation(const Date& dateProg, const Horaire& horaireProg) const {
    return const_cast<ProgrammationManager*>(this)->getProgrammation(dateProg, horaireProg);
}


ProgrammationTacheSimpleNonPreemptive& ProgrammationManager::addProgrammationTacheSimpleNonPreemptive(const Date& dateProg, const Horaire& horaireProg, TacheSimpleNonPreemptive& tache) {
    if(!isValid(dateProg, horaireProg, tache.getDuree())) {
        throw ProgrammationManagerException("Erreur, ProgrammationManager, addProgrammationTacheSimpleNonPreemptive, Programmation incompatible avec une programmation existante");
    }
    if(!tache.estDansIntervalle(dateProg, horaireProg)){
        throw ProgrammationManagerException("Erreur, ProgrammationManager, addProgrammationTacheSimpleNonPreemptive, Programmation ne respectant pas la disponibilité ou l'échéance de la tâche");
    }
    for(Tache::tp_const_iterator it = tache.tPBegin(); it != tache.tPEnd(); ++it){
        // on parcourt toutes les tâches précédentes de la tâche que l'on souhaite programmer
        // (*it) pour accéder à la tâche *
        // -> pour accéder à la méthode
        if(!(it->second->checkProgrammationCoherente(dateProg, horaireProg))){
            throw ProgrammationManagerException("Désolé, votre programmation de tâche entre en conflit avec une de ses tâches précédentes");
        }
    }
    ProgrammationTacheSimpleNonPreemptive* programmation = new ProgrammationTacheSimpleNonPreemptive(dateProg, horaireProg,tache);
    Manager::addItem(getKeyFrom(dateProg, horaireProg), programmation);
    return *programmation;
}
ProgrammationTacheSimplePreemptive& ProgrammationManager::addProgrammationTacheSimplePreemptive(const Date& dateProg, const Horaire& horaireProg, unsigned int pourcentage, TacheSimplePreemptive& tache) {
    if(tache.getPourcentageDejaProgramme() == 100){
        throw ProgrammationManagerException("Erreur, ProgrammationManager, addProgrammationTacheSimplePreemptive, la tâche a déjà été programmée");
    }
    if(!isValid(dateProg, horaireProg, tache.getDureeProgrammationViaPourcentage(pourcentage))) {
        throw ProgrammationManagerException("Erreur, ProgrammationManager, addProgrammationTacheSimplePreemptive, Programmation incompatible avec une programmation existante");
    }
    if(!tache.estDansIntervalle(dateProg, horaireProg,pourcentage)){
        throw ProgrammationManagerException("Erreur, ProgrammationManager, addProgrammationTacheSimplePreemptive, Programmation ne respectant pas la disponibilité ou l'échéance de la tâche");
    }
    if(tache.getPourcentageDejaProgramme()+pourcentage>100){
        throw ProgrammationManagerException("Erreur, ProgrammationManager, addProgrammationTacheSimplePreemptive, le pourcentage de la tâche a été sélectionné de telle manière qu'il dépasse les 100 %");
    }
    for(Tache::tp_const_iterator it = tache.tPBegin(); it != tache.tPEnd(); ++it){
        // on parcourt toutes les tâches précédentes de la tâche que l'on souhaite programmer
        // (*it) pour accéder à la tâche *
        // -> pour accéder à la méthoe
        // std::cout << typeid(*(it->second)).name(); -> test
        if(!(it->second->checkProgrammationCoherente(dateProg, horaireProg))){
            throw ProgrammationManagerException("Désolé, votre programmation de tâche entre en conflit avec une de ses tâches précédentes ou ces dernières n'ont pas encore été programmées");
        }
    }
    ProgrammationTacheSimplePreemptive* programmation = new ProgrammationTacheSimplePreemptive(dateProg, horaireProg, pourcentage,tache);
    Manager::addItem(getKeyFrom(dateProg, horaireProg), programmation);
    return *programmation;
}

void ProgrammationManager::exportTo(QXmlStreamWriter& stream) {
    stream.writeStartElement("ProgrammationManager");
    for(iterator it=begin(); it!=end(); ++it){
        if(typeid(*it->second)==typeid(ProgrammationEvenement)) {
            (*it->second).exportTo(stream);
        }
    }
    stream.writeEndElement();
}

void ProgrammationManager::loadFrom(QXmlStreamReader &xml) {
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "ProgrammationManager")) {
        xml.readNextStartElement();
        if(xml.name() == "ProgrammationEvenement") {
            std::string dateProgrammation;
            std::string horaireProgrammation;
            std::string duree;

            xml.readNext();
            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "ProgrammationEvenement")) {
                if(xml.tokenType() == QXmlStreamReader::StartElement) {
                    if(xml.name() == "dateProgrammation") {
                        xml.readNext();
                        dateProgrammation=toString(xml.text().toString());
                    }
                    if(xml.name() == "horaireProgrammation") {
                        xml.readNext();
                        horaireProgrammation=toString(xml.text().toString());
                    }
                    if(xml.name() == "duree") {
                        xml.readNext();
                        duree=toString(xml.text().toString());
                    }
                    if(xml.name() == "RendezVous" || xml.name() == "Reunion") {
                        xml.readNext();
                        ProgrammationEvenement& pe = addProgrammationEvenement(Date(dateProgrammation),Horaire(horaireProgrammation),Duree(duree));
                        pe.loadFrom(xml);
                    }
                }
                xml.readNext();
            }
        }
    }
}

void ProgrammationManager::loadListeProgrammations(QXmlStreamReader &xml, Tache& tache, bool preemptive) {
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "ListeProgrammations")) {
        xml.readNextStartElement();
        if(xml.name() == "ProgrammationTacheSimplePreemptive" || xml.name() == "ProgrammationTacheSimpleNonPreemptive") {
            std::string dateProgrammation;
            std::string horaireProgrammation;
            std::string pourcentage;
            xml.readNext();
            while(!(xml.tokenType() == QXmlStreamReader::EndElement && (xml.name() == "ProgrammationTacheSimpleNonPreemptive" || xml.name() == "ProgrammationTacheSimplePreemptive"))) {
                if(xml.tokenType() == QXmlStreamReader::StartElement) {
                    if(xml.name() == "dateProgrammation") {
                        xml.readNext();
                        dateProgrammation=toString(xml.text().toString());
                    }else if(xml.name() == "horaireProgrammation") {
                        xml.readNext();
                        horaireProgrammation=toString(xml.text().toString());
                    }else if(xml.name() == "pourcentage") {
                        xml.readNext();
                        pourcentage=toString(xml.text().toString());
                    }
                }
                xml.readNext();
            }
            if(preemptive) {
                addProgrammationTacheSimplePreemptive(Date(dateProgrammation),Horaire(horaireProgrammation),atoi(pourcentage.c_str()),dynamic_cast<TacheSimplePreemptive&>(tache));
            }else {
                addProgrammationTacheSimpleNonPreemptive(Date(dateProgrammation),Horaire(horaireProgrammation),dynamic_cast<TacheSimpleNonPreemptive&>(tache));
            }
        }
    }
}

void ProgrammationManager::exportContraintes(QXmlStreamWriter& stream, const Date& dateDebut, const Date& dateFin,const Horaire& horaireDebut, const Horaire& horaireFin) {
    stream.writeStartElement("Programmation");
    for(iterator it=constraint_begin(dateDebut,horaireDebut); it!=constraint_end(dateFin,horaireFin); ++it){
        if(typeid(*it->second)==typeid(ProgrammationEvenement)) {
            (*it->second).exportTo(stream);
        }
    }
    stream.writeEndElement();
}
