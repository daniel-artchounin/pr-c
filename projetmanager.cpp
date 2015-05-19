#include "projetmanager.h"
#include "projetmanagerexception.h"
#include "date.h"
#include "horaire.h"
#include "duree.h"
#include <string>

//design pattern singleton
ProjetManager * ProjetManager::instance=0; //initialisation à null, pour la première vérification

ProjetManager& ProjetManager::getInstance() {
    //si l'instance interne n'est pas encore créé, on doit le faire
    if(!instance) instance = new ProjetManager();
    return *instance;
}

void ProjetManager::libererInstance() {
    if(!instance) delete instance;
}

void ProjetManager::addItem(Projet* projet) {
    if (nb==nbMax) {
        Projet** newtab=new Projet*[nbMax+10];
        for(unsigned int i=0; i<nb; i++) newtab[i]=projets[i];
        nbMax+=10;
        Projet** old=projets;
        projets=newtab;
        delete[] old;
    }
    projets[nb++]=projet;
}

Projet* ProjetManager::trouverProjet(const std::string& titre)const {
    for(unsigned int i=0; i<nb; i++)
        if (titre==projets[i]->getTitre()) return projets[i];
    return 0;
}

Projet& ProjetManager::ajouterProjet(const Date& dateDebut, const Horaire& horaireDebut, const Date& dateFin, const Horaire& horaireFin, const std::string& titre) {
    if (trouverProjet(titre)) throw ProjetManagerException("erreur, ProjetManager, Projet deja existante");
    Projet* newt=new Projet(dateDebut,horaireDebut,dateFin,horaireFin,titre);
    addItem(newt);
    return *newt;
}

Projet& ProjetManager::getProjet(const std::string& id) {
    Projet* t=trouverProjet(id);
    if (!t) throw ProjetManagerException("erreur, ProjetManager, Projet inexistante");
    return *t;
}

const Projet& ProjetManager::getProjet(const std::string& id)const {
    return const_cast<ProjetManager*>(this)->getProjet(id);
}

ProjetManager::~ProjetManager() {
    for(unsigned int i=0; i<nb; i++) delete projets[i];
    delete[] projets;
}

/*
ProjetManager::ProjetManager(const ProjetManager& pm) : projets(new Projet*[pm.nb]), nb(pm.nb), nbMax(pm.nbMax) {
    for(unsigned int i=0; i<nb; i++) projets[i]=new Projet(*pm.projets[i]);
}

ProjetManager& ProjetManager::operator=(const ProjetManager& pm) {
    if (this==&pm) return *this;
    this->~ProjetManager();
    projets=pm.projets;
    return *this;
}
*/
