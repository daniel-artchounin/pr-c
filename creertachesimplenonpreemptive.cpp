#include "creertachesimplenonpreemptive.h"

CreerTacheSimpleNonPreemptive::CreerTacheSimpleNonPreemptive(Projet& projet, std::string * chaine, unsigned int* taille, QWidget *parent) :
    CreerTache(projet, chaine, taille, parent)
{
    heures = new QSpinBox;
    labelH = new QLabel("heure(s)");
    minutes =  new QSpinBox;
    minutes->setRange(0,59);
    labelM = new QLabel("minute(s)");
    hBox1 = new QHBoxLayout;
    hBox1->addWidget(heures);
    hBox1->addWidget(labelH);
    hBox1->addWidget(minutes);
    hBox1->addWidget(labelM);
    formlayout->addRow("Durée : ", hBox1);
    vBox->addLayout(formlayout);
    vBox->addLayout(hBoxAnnulerValider);
}

void CreerTacheSimpleNonPreemptive::retourFenetrePrincipaleValider(){
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
                    false,
                    Duree(heures->value(), minutes->value()));
        QMessageBox::information(this, "Création de tâche simple non préemptive", "Votre tâche simple non préemptive " + titre->text() +" a bien été créée.");
    }
    catch(std::logic_error& e){
        QMessageBox::warning(this, "Création de tâche tâche simple non préemptive", e.what());
    }
    this->close();
}
