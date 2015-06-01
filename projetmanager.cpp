#include "projetmanager.h"
#include "projetmanagerexception.h"
# include <QDebug>
#include "tools.h"


//design pattern singleton
ProjetManager * ProjetManager::instance=0; //initialisation à null, pour la première vérification

ProjetManager& ProjetManager::getInstance() {
    //si l'instance interne n'est pas encore créé, on doit le faire
    std::cout << "instance" << instance << std::endl;
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

void ProjetManager::loadFrom(QXmlStreamReader& xml) {
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "ProjetManager")) {
        xml.readNextStartElement();
        if(xml.name() == "Projet") {
            std::string titre;
            std::string dateDebut;
            std::string horaireDebut;
            std::string dateFin;
            std::string horaireFin;
            xml.readNext();
            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Projet")) {
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
                    }else if(xml.name() == "ListeTaches") {
                        xml.readNext();
                        Projet& projet = addProjet(titre,dateDebut,horaireDebut,dateFin,horaireFin);
                        std::vector<std::string> vect=std::vector<std::string>();
                        projet.loadFrom(xml,vect);
                    }
                }
                xml.readNext();
            }
        }
    }
}
