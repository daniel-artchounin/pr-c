#include "informationstachesimplenonpreemptive.h"
# include "programmationtachesimplenonpreemptive.h"

InformationsTacheSimpleNonPreemptive::InformationsTacheSimpleNonPreemptive(const TacheSimpleNonPreemptive& tacheSimpleNonPreemptive, QWidget *parent):
    InformationsTacheSimple(tacheSimpleNonPreemptive, parent)
{
    if(tacheSimpleNonPreemptive.getProgrammation()!=0){
        dateDebutP = new QLabel(QString::fromStdString(tacheSimpleNonPreemptive.getProgrammation()->getDateProgrammation().toString()));
        horaireDebutP = new QLabel(QString::fromStdString(tacheSimpleNonPreemptive.getProgrammation()->getHoraireProgrammation().toString()));
        dateEcheanceP = new QLabel(QString::fromStdString(tacheSimpleNonPreemptive.getProgrammation()->getDateFin().toString()));
        heureEcheanceP = new QLabel(QString::fromStdString(tacheSimpleNonPreemptive.getProgrammation()->getHoraireFin().toString()));
        formlayout->addRow("Horaire de programmation : ", dateDebutP);
        formlayout->addRow("Date de début de programmation : ", horaireDebutP);
        formlayout->addRow("Date de fin de programmation : ", dateEcheanceP);
        formlayout->addRow("Horaire de fin de programmation : ", heureEcheanceP);
    }
    vBox->addLayout(formlayout);
    if(vBoxPrecedence!=0){
        vBox->addLayout(vBoxPrecedence);
    }
    vBox->addLayout(hBoxOK);
}
