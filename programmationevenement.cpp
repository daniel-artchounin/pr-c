#include "programmationevenement.h"
#include "programmationevenementexception.h"
#include "reunion.h"
#include "rendezvous.h"

ProgrammationEvenement::~ProgrammationEvenement(){}

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
