# include "creertachecomposite.h"
# include "fenetreprincipale.h"
# include <QCloseEvent>
# include <stdexcept>
# include <QMessageBox>

CreerTacheComposite::CreerTacheComposite(Projet& projet, std::string * chaine, unsigned int* taille, QWidget *parent) :
    CreerTache(projet, chaine, taille, parent)
{
    vBox->addLayout(formlayout);
    vBox->addLayout(hBoxAnnulerValider);
}

void CreerTacheComposite::retourFenetrePrincipaleValider(){
    try{
        nomProjet.creerAjouterTache(
                    chemin,
                    *tailleChemin,
                    Date(dateDebut->date().day(), dateDebut->date().month(), dateDebut->date().year()),
                    Horaire(horaireDebut->time().hour(), horaireDebut->time().minute()),
                    Date(dateFin->date().day(), dateFin->date().month(), dateFin->date().year()),
                    Horaire(horaireFin->time().hour(), horaireFin->time().minute()),
                    titre->text().toStdString(),
                    false,
                    true
                    );
        QMessageBox::information(this, "Création de tâche composite", "Votre tâche composite " + titre->text() +" a bien été créée.");
    }
    catch(std::logic_error& e){
        QMessageBox::warning(this, "Création de tâche composite", e.what());
    }
    this->close();
}

