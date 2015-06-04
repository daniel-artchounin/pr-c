#include "creerprojet.h"
# include <QPushButton>
# include <fenetreprincipale.h>
# include <QCloseEvent>
# include "date.h"
# include "time.h"
# include "projetmanagerexception.h"
# include <QMessageBox>

CreerProjet::CreerProjet(QWidget *parent) :
    QWidget(parent)
{
    titre = new QLineEdit;
    dateDebut = new QDateEdit();
    horaireDebut = new QTimeEdit();
    dateFin = new QDateEdit();
    horaireFin = new QTimeEdit();
    formlayout = new QFormLayout;
    formlayout->addRow("Titre du projet : ", titre);
    formlayout->addRow("Date de disponibilité du projet : ", dateDebut);
    formlayout->addRow("Horaire de disponibilité du projet : ", horaireDebut);
    formlayout->addRow("Date d'échéance du projet : ", dateFin);
    formlayout->addRow("Horaire d'échéance du projet : ", horaireFin);
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

void CreerProjet::retourFenetrePrincipaleAnnuler(){
    FenetrePrincipale& fenetrePrincipal = FenetrePrincipale::getInstance();
    fenetrePrincipal.show();
    this->close();
}

void CreerProjet::retourFenetrePrincipaleSauver(){
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

void CreerProjet::closeEvent(QCloseEvent *event)
{
    FenetrePrincipale& fenetrePrincipal = FenetrePrincipale::getInstance();
    fenetrePrincipal.show();
    event->accept();

}
