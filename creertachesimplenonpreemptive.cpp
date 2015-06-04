#include "creertachesimplenonpreemptive.h"

CreerTacheSimpleNonPreemptive::CreerTacheSimpleNonPreemptive(Projet& projet, std::string * chaine, unsigned int* taille, QWidget *parent) :
    QWidget(parent), nomProjet(projet)
{
    chemin = chaine;
    tailleChemin = taille;
    titre = new QLineEdit;
    dateDebut = new QDateEdit();
    horaireDebut = new QTimeEdit();
    dateFin = new QDateEdit();
    horaireFin = new QTimeEdit();
    formlayout = new QFormLayout;
    heures = new QSpinBox;
    labelH = new QLabel("heure(s)");
    minutes =  new QSpinBox;
    labelM = new QLabel("minute(s)");
    formlayout->addRow("Titre de la tâche simple non préemptive : ", titre);
    formlayout->addRow("Date de disponibilité : ", dateDebut);
    formlayout->addRow("Horaire de disponibilité : ", horaireDebut);
    formlayout->addRow("Date d'échéance : ", dateFin);
    formlayout->addRow("Horaire d'échéance : ", horaireFin);
    hBox1 = new QHBoxLayout;
    hBox1->addWidget(heures);
    hBox1->addWidget(labelH);
    hBox1->addWidget(minutes);
    hBox1->addWidget(labelM);
    formlayout->addRow("Durée : ", hBox1);
    annuler = new QPushButton("Annuler");
    sauver = new QPushButton("Sauver");
    hBox2 = new QHBoxLayout;
    hBox2->addWidget(annuler);
    hBox2->addWidget(sauver);
    vBox = new QVBoxLayout(this);
    vBox->addLayout(formlayout);
    vBox->addLayout(hBox2);
    connect(annuler,SIGNAL(clicked()),this,SLOT(retourFenetrePrincipaleAnnuler()));
    connect(sauver,SIGNAL(clicked()),this,SLOT(retourFenetrePrincipaleSauver()));
}


void CreerTacheSimpleNonPreemptive::retourFenetrePrincipaleAnnuler(){
    delete[] chemin;
    chemin = 0;
    delete tailleChemin;
    tailleChemin = 0;
    FenetrePrincipale& fenetrePrincipal = FenetrePrincipale::getInstance();
    fenetrePrincipal.show();
    this->close();
}

void CreerTacheSimpleNonPreemptive::retourFenetrePrincipaleSauver(){
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
    }
    catch(std::logic_error& e){
        QMessageBox::warning(this, "Création de tâche tâche simple non préemptive", e.what());
    }
    this->close();
}

void CreerTacheSimpleNonPreemptive::closeEvent(QCloseEvent *event)
{
    if(chemin!=0){
        delete[] chemin;
        chemin = 0;
    }
    if(tailleChemin!=0){
        delete tailleChemin;
        tailleChemin = 0;
    }
    FenetrePrincipale& fenetrePrincipal = FenetrePrincipale::getInstance();
    fenetrePrincipal.show();
    event->accept();

}
