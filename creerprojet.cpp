#include "creerprojet.h"
# include <QPushButton>
# include <fenetreprincipale.h>
# include <QCloseEvent>
# include "date.h"
# include "time.h"
# include "projetmanagerexception.h"
# include <QMessageBox>

CreerProjet::CreerProjet(QWidget *parent) :
    CreerProjetTache(parent)
{
    vBox->addLayout(formlayout);
    vBox->addLayout(hBoxAnnulerValider);
}

void CreerProjet::retourFenetrePrincipaleValider(){
    ProjetManager& projetMangager = ProjetManager::getInstance();
    try{
        projetMangager.addProjet(
            titre->text().toStdString(),
            Date(dateDebut->date().day(), dateDebut->date().month(), dateDebut->date().year()),
            Horaire(horaireDebut->time().hour(), horaireDebut->time().minute()),
            Date(dateFin->date().day(), dateFin->date().month(), dateFin->date().year()),
            Horaire(horaireFin->time().hour(), horaireFin->time().minute())
        );
    }
    catch(ProjetManagerException& e){
        QMessageBox::warning(this, "Création de projet", e.what());
    }
    this->close();
}
