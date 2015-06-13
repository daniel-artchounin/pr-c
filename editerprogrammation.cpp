#include "editerprogrammation.h"
#include "fenetreprincipale.h"
#include "programmationevenement.h"
#include "programmationtachesimplenonpreemptive.h"
#include "programmationtachesimplepreemptive.h"
#include <typeinfo>
#include <QListWidget>
#include "reunion.h"
#include "rendezvous.h"

EditerProgrammation::EditerProgrammation(QWidget *parent) : QWidget(parent) {
    form=0;
    list=new QListWidget;
    select=new QPushButton("Sélectionner");
    suppr=new QPushButton("Supprimer");
    vBox=new QVBoxLayout;
    vBox->addWidget(list);
    hBoxButon=new QHBoxLayout;
    hBoxButon->addWidget(select);
    hBoxButon->addWidget(suppr);
    vBox->addLayout(hBoxButton);
    hBox=new QHBoxLayout;
    hBox->addLayout(vBox);
    this->setLayout(hBox);
    updateListe();
    connect(select,SIGNAL(clicked()),this,SLOT(selectionner()));
    connect(suppr,SIGNAL(clicked()),this,SLOT(supprimer()));
}


void EditerProgrammation::updateListe() {
    list->clear();
    ProgrammationManager& pgm=ProgrammationManager::getInstance();
    for(ProgrammationManager::iterator it=pgm.begin(); it!=pgm.end(); ++it) {
        QListWidgetItem *widget = new QListWidgetItem;
        widget->setText(toQString(it->second->getNom()));
        widget->setData(101, toQString(it->second->getDateProgrammation().toString()));
        widget->setData(102, toQString(it->second->getHoraireProgrammation().toString()));
        list->addItem(widget);
    }
}

void EditerProgrammation::closeEvent(QCloseEvent *event) {
    event->accept();
    FenetrePrincipale& fp = FenetrePrincipale::getInstance();
    fp.show();
    fp.updateEDT();
}

void EditerProgrammation::supprimer() {
    QListWidgetItem* item= list->currentItem();
    if(item) {
        if(form!=0) {
            delete form;
        }
        ProgrammationManager &pgm = ProgrammationManager::getInstance();
        pgm.deleteProgrammation(&pgm.getProgrammation(Date(toString(item->data(101).toString())), Horaire(toString(item->data(102).toString()))));
        updateListe();
    }
}

void EditerProgrammation::selectionner() {
    QListWidgetItem* it= list->currentItem();
    if(it) {
        if(form!=0) {
            delete form;
        }
        Programmation &prog=ProgrammationManager::getInstance().getProgrammation(Date(toString(it->data(101).toString())),Horaire(toString(it->data(102).toString())));
        if(typeid(prog)==typeid(ProgrammationEvenement)) {
            ProgrammationEvenement& progEvt=dynamic_cast<ProgrammationEvenement&>(prog);
            if(typeid(*progEvt.getEvenement())==typeid(RendezVous)) {
                form = new ProgrammerRendezVous(&progEvt,this);
            }else if(typeid(*progEvt.getEvenement())==typeid(Reunion)) {
                form = new ProgrammerReunion(&progEvt,this);
            }
        }else if(typeid(prog)==typeid(ProgrammationTacheSimpleNonPreemptive)) {
            ProgrammationTacheSimpleNonPreemptive& progTache=dynamic_cast<ProgrammationTacheSimpleNonPreemptive&>(prog);
            form = new ProgrammerTacheSimpleNonPreemptive(&progTache);
        }else if(typeid(prog)==typeid(ProgrammationTacheSimplePreemptive)) {
            ProgrammationTacheSimplePreemptive& progTache=dynamic_cast<ProgrammationTacheSimplePreemptive&>(prog);
            form = new ProgrammerTacheSimplePreemptive(&progTache);
        }
        hBox->addWidget(form);
    }
}

