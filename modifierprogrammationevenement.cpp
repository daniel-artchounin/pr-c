#include "modifierprogrammationevenement.h"
#include "fenetreprincipale.h"
#include "programmationevenement.h"
#include <typeinfo>
#include <QListWidget>
#include "reunion.h"
#include "rendezvous.h"

ModifierProgrammationEvenement::ModifierProgrammationEvenement(QWidget *parent) : QWidget(parent) {
    form=0;
    list=new QListWidget;
    select=new QPushButton("Sélectionner");
    vBox=new QVBoxLayout;
    vBox->addWidget(list);
    vBox->addWidget(select);
    hBox=new QHBoxLayout;
    hBox->addLayout(vBox);
    this->setLayout(hBox);
    initialiseListe();
    connect(select,SIGNAL(clicked()),this,SLOT(selectionner()));
}

void ModifierProgrammationEvenement::initialiseListe() {
    ProgrammationManager& pgm=ProgrammationManager::getInstance();
    for(ProgrammationManager::iterator it=pgm.begin(); it!=pgm.end(); ++it) {
        if(typeid(*it->second)==typeid(ProgrammationEvenement)) {
            QListWidgetItem *widget = new QListWidgetItem;
            widget->setText(toQString(it->second->getNom()));
            widget->setData(101, toQString(it->second->getDateProgrammation().toString()));
            widget->setData(102, toQString(it->second->getHoraireProgrammation().toString()));
            list->addItem(widget);
        }
    }
}

void ModifierProgrammationEvenement::quitter() {
    this->close();
}

void ModifierProgrammationEvenement::closeEvent(QCloseEvent *event) {
    event->accept();
    FenetrePrincipale& fp = FenetrePrincipale::getInstance();
    fp.show();
    fp.updateEDT();
}

void ModifierProgrammationEvenement::selectionner() {
    QListWidgetItem* it= list->currentItem();
    if(form!=0) {
        delete form;
    }
    ProgrammationEvenement &prog=dynamic_cast<ProgrammationEvenement&>(ProgrammationManager::getInstance().getProgrammation(Date(toString(it->data(101).toString())),Horaire(toString(it->data(102).toString()))));
    if(typeid(*prog.getEvenement())==typeid(RendezVous)) {
        form = new ProgrammerRendezVous(&prog);
        hBox->addWidget(form);
    }else if(typeid(*prog.getEvenement())==typeid(Reunion)) {
        form = new ProgrammerReunion(&prog);
        hBox->addWidget(form);
    }
}

