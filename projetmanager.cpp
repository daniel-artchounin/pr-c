#include "projetmanager.h"
#include "projetmanagerexception.h"

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

Projet& ProjetManager::addProjet(const std::string titre, const Date dateDebut, const Horaire horaireDebut, const Date dateFin, const Horaire horaireFin) {
    Projet* projet = new Projet(dateDebut, horaireDebut, dateFin, horaireFin, titre);
    if(!Manager::addItem(titre, projet)) {
        throw ProjetManagerException("Erreur, ProjetManager, addProjet, Projet deja existant");
    }
    return *projet;
}

Projet& ProjetManager::getProjet(const std::string& titre) {
    Projet* projet=getItem(titre);
    if (!projet) throw ProjetManagerException("erreur, ProjetManager, getProjet, Projet inexistant");
    return *projet;
}

const Projet& ProjetManager::getProjet(const std::string& id)const {
    return const_cast<ProjetManager*>(this)->getProjet(id);
}
