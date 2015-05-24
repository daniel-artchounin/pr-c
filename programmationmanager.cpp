#include "programmationmanager.h"
#include "programmationevenement.h"
#include "programmationmanagerexception.h"
#include "iostream"

//design pattern singleton
ProgrammationManager * ProgrammationManager::instance=0; //initialisation à null, pour la première vérification

ProgrammationManager& ProgrammationManager::getInstance() {
    //si l'instance interne n'est pas encore créé, on doit le faire
    if(!instance) instance = new ProgrammationManager();
    return *instance;
}

void ProgrammationManager::libererInstance() {
    if(!instance) delete instance;
}

bool ProgrammationManager::inclus(const Date dateProg, const Horaire horaireProg, const Date dateFin, const Horaire horaireFin, const Date date, const Horaire horaire) const {
    return (dateProg<date || (dateProg==date && horaireProg<=horaire)) && (date<dateFin || (date==dateFin && horaire<=horaireFin));
}

bool ProgrammationManager::hasIntersection(const Date dateProg, const Horaire horaireProg, const Date dateFin, const Horaire horaireFin, const Date newDate, const Horaire newHoraire, const Duree newDuree) const{
    return inclus(dateProg, horaireProg, dateFin, horaireFin, newDate, newHoraire) || inclus(newDate, newHoraire, newDate.addDuree(newDuree), newHoraire.addDuree(newDuree), dateProg, horaireProg);
}

bool ProgrammationManager::isValid(const Date date, const Horaire horaire, const Duree duree) {
    for(iterator it=begin(); it!=end(); it++) {
        Programmation& prog = *it->second;
        if(hasIntersection(prog.getDateProgrammation(), prog.getHoraireProgrammation(), prog.getDateFin(), prog.getHoraireFin(), date, horaire, duree)) {
            return false;
        }
    }
    return true;
}

std::string ProgrammationManager::getKeyFrom(const Date date, const Horaire horaire) {
    return date.formatAAAAMMJJ()+horaire.formatHHMM();
}

Programmation& ProgrammationManager::addProgrammationEvenement(const Date dateProg, const Horaire horaireProg, const Duree duree) {
    if(items.find(getKeyFrom(dateProg, horaireProg))!=end() || !isValid(dateProg, horaireProg, duree)) {
        throw ProgrammationManagerException("Erreur, ProgrammationManager, addProgrammationEvenement, Programmation incompatible avec une programmation existante");
    }
    ProgrammationEvenement* programmation = new ProgrammationEvenement(dateProg, horaireProg, duree);
    Manager::addItem(getKeyFrom(dateProg, horaireProg), programmation);
    return *programmation;
}

Programmation& ProgrammationManager::getProgrammation(const Date dateProg, const Horaire horaireProg) {
    Programmation* programmation=getItem(getKeyFrom(dateProg, horaireProg));
    if (!programmation) throw ProgrammationManagerException("erreur, ProgrammationManager, getProgrammation, Programmation inexistante");
    return *programmation;
}

const Programmation& ProgrammationManager::getProgrammation(const Date dateProg, const Horaire horaireProg) const {
    return const_cast<ProgrammationManager*>(this)->getProgrammation(dateProg, horaireProg);
}
