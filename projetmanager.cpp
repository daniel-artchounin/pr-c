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

Projet& ProjetManager::addProjet(const std::string& titre, const Date& dateDebut, const Horaire& horaireDebut, const Date& dateFin, const Horaire& horaireFin) {
    if(getItem(titre)) {
        throw ProjetManagerException("Erreur, ProjetManager, addProjet, Projet deja existant");
    }
    Projet* projet = new Projet(dateDebut, horaireDebut, dateFin, horaireFin, titre);
    Manager::addItem(titre, projet);
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

void ProjetManager::exportTo(QXmlStreamWriter& stream) {
    stream.writeStartElement("ProjetManager");
    Manager::exportTo(stream);
    stream.writeEndElement();
}
