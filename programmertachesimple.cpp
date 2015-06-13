#include "programmertachesimple.h"
# include <QMessageBox>

ProgrammerTacheSimple::ProgrammerTacheSimple(Projet* projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent):
    FenetreAnnulerValider(parent), nomProjet(projet), progTache(0)
{

    try{
        Tache& myTache = nomProjet->accederTache(
                    chaine,
                    *taille,
                    titreT
                    );
        titre = new QLabel(QString::fromStdString(myTache.getTitre()));
        dateDebut = new QLabel(QString::fromStdString(myTache.getDateDebut().toString()));
        horaireDebut = new QLabel(QString::fromStdString(myTache.getHoraireDebut().toString()));
        dateEcheance = new QLabel(QString::fromStdString(myTache.getDateFin().toString()));
        heureEcheance = new QLabel(QString::fromStdString(myTache.getHoraireFin().toString()));
        duree = new QLabel(QString::fromStdString(myTache.getDuree().toString()));
    }catch(std::logic_error& e){
        QMessageBox::warning(this,"Programmation de tâche", "L'élément sélectionné n'est pas une tâche");
        this->close();
    }
    titreTache = titreT;
    chemin = chaine;
    tailleChemin = taille;
    dateProgrammation = new QDateEdit(QDate::currentDate());
    horaireProgrammation = new QTimeEdit(QTime::currentTime());
    formlayout = new QFormLayout;
    formlayout->addRow("Titre :",titre);
    formlayout->addRow("Date de disponibilité : ",dateDebut);
    formlayout->addRow("Date de début de programmation",horaireDebut);
    formlayout->addRow("Horaire de disponibilité : ",dateEcheance);
    formlayout->addRow("Date d'échéance : ",heureEcheance);
    formlayout->addRow("Duree : ",duree);
    formlayout->addRow("Date de début de programmation",dateProgrammation);
    formlayout->addRow("Horaire de début de programmation",horaireProgrammation);
    vBox->addLayout(formlayout);
    vBox->addLayout(hBoxAnnulerValider);
}

ProgrammerTacheSimple::ProgrammerTacheSimple(ProgrammationTacheSimple* prog, QWidget *parent):
    FenetreAnnulerValider(parent), nomProjet(0), progTache(prog)
{
    titre = new QLabel;
    duree = new QLabel;
    titre = new QLabel;
    dateDebut = new QLabel;
    horaireDebut = new QLabel;
    dateEcheance = new QLabel;
    heureEcheance = new QLabel;
    duree = new QLabel;
    titreTache = progTache->getNom();
    chemin = 0;
    tailleChemin = 0;
    dateProgrammation = new QDateEdit(QDate(prog->getDateProgrammation().getAnnee(), prog->getDateProgrammation().getMois(), prog->getDateProgrammation().getJour()));
    horaireProgrammation = new QTimeEdit(QTime(prog->getHoraireProgrammation().getHeure(),prog->getHoraireProgrammation().getMinute()));
    formlayout = new QFormLayout;
    formlayout->addRow("Titre :",titre);
    formlayout->addRow("Date de disponibilité : ",dateDebut);
    formlayout->addRow("Date de début de programmation",horaireDebut);
    formlayout->addRow("Horaire de disponibilité : ",dateEcheance);
    formlayout->addRow("Date d'échéance : ",heureEcheance);
    formlayout->addRow("Duree : ",duree);
    formlayout->addRow("Date de début de programmation",dateProgrammation);
    formlayout->addRow("Horaire de début de programmation",horaireProgrammation);
    vBox->addLayout(formlayout);
    vBox->addLayout(hBoxAnnulerValider);
}

void ProgrammerTacheSimple::closeEvent(QCloseEvent *event){
    if(chemin!=0){
        delete[] chemin;
        chemin = 0;
    }
    if(tailleChemin!=0){
        delete tailleChemin;
        tailleChemin = 0;
    }
    if(progTache==0) {
        FenetreAnnulerValider::closeEvent(event);
    }else {
        this->close();
    }
}
