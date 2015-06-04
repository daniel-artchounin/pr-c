# include "creertachecomposite.h"
# include "fenetreprincipale.h"
# include <QCloseEvent>
# include <stdexcept>
# include <QMessageBox>

CreerTacheComposite::CreerTacheComposite(Projet& projet, std::string * chaine, unsigned int* taille, QWidget *parent) :
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
    formlayout->addRow("Titre de la tâche composite :", titre);
    formlayout->addRow("Date de disponibilité : ", dateDebut);
    formlayout->addRow("Horaire de disponibilité : ", horaireDebut);
    formlayout->addRow("Date d'échéance : ", dateFin);
    formlayout->addRow("Horaire d'échéance : ", horaireFin);
    annuler = new QPushButton("Annuler");
    sauver = new QPushButton("Sauver");
    hBox = new QHBoxLayout;
    hBox->addWidget(annuler);
    hBox->addWidget(sauver);
    vBox = new QVBoxLayout(this);
    vBox->addLayout(formlayout);
    vBox->addLayout(hBox);
    connect(annuler,SIGNAL(clicked()),this,SLOT(retourFenetrePrincipaleAnnuler()));
    connect(sauver,SIGNAL(clicked()),this,SLOT(retourFenetrePrincipaleSauver()));
}

void CreerTacheComposite::retourFenetrePrincipaleAnnuler(){
    delete[] chemin;
    chemin = 0;
    delete tailleChemin;
    tailleChemin = 0;
    FenetrePrincipale& fenetrePrincipal = FenetrePrincipale::getInstance();
    fenetrePrincipal.show();
    this->close();
}

void CreerTacheComposite::retourFenetrePrincipaleSauver(){
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
    }
    catch(std::logic_error& e){
        QMessageBox::warning(this, "Création de tâche composite", e.what());
    }
    this->close();
}

void CreerTacheComposite::closeEvent(QCloseEvent *event)
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
