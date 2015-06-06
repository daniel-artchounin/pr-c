#include "programmationevenement.h"
#include "programmationevenementexception.h"
#include "reunion.h"
#include "rendezvous.h"
#include "tools.h"

ProgrammationEvenement::~ProgrammationEvenement(){
    delete evenement;
}

Evenement& ProgrammationEvenement::programmerReunion(const std::string nom, const std::string lieu, const std::string motif) {
    if(evenement) {
        throw ProgrammationEvenementException("erreur: évènement déjà programmé");
    }
    evenement=new Reunion(nom, lieu, motif);
    return *evenement;
}

Evenement& ProgrammationEvenement::programmerRendezVous(const std::string nom, const std::string lieu, const std::string motif) {
    if(evenement) {
        throw ProgrammationEvenementException("erreur: évènement déjà programmé");
    }
    evenement=new RendezVous(nom, lieu, motif);
    return *evenement;
}

void ProgrammationEvenement::exportTo(QXmlStreamWriter& stream) {
    stream.writeStartElement("ProgrammationEvenement");
    Programmation::exportTo(stream);
    evenement->exportTo(stream);
    stream.writeEndElement();
}

void ProgrammationEvenement::loadFrom(QXmlStreamReader &xml) {
    std::string nom;
    std::string lieu;
    std::string motif;
    xml.readNext();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && (xml.name() == "Reunion" || xml.name() == "RendezVous"))) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            if(xml.name() == "nom") {
                xml.readNext();
                nom=toString(xml.text().toString());
            }
            if(xml.name() == "lieu") {
                xml.readNext();
                lieu=toString(xml.text().toString());
            }
            if(xml.name() == "motif") {
                xml.readNext();
                motif=toString(xml.text().toString());
            }
        }
        xml.readNext();
    }
    if(xml.name()=="Reunion") {
        programmerReunion(nom,lieu,motif);
    }else {
        programmerRendezVous(nom,lieu,motif);
    }
}

Duree ProgrammationEvenement::getDuree() const{
    return duree;
}

std::string ProgrammationEvenement::getNom() const{
    return evenement->getNom();
}
