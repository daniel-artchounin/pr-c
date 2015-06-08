#include "informationstachesimplepreemptive.h"
# include "programmationtachesimplepreemptive.h"
# include "informationstache.h"
# include <QDesktopWidget>
# include <QApplication>
# include <sstream>

InformationsTacheSimplePreemptive::InformationsTacheSimplePreemptive(const TacheSimplePreemptive& tacheSimplePreemptive, QWidget *parent):
    InformationsTacheSimple(tacheSimplePreemptive, parent)
{
    programmationsTableWidget = 0;
    if(tacheSimplePreemptive.pSize() > 0){
        programmationsTableWidget = new QTableWidget();
        QStringList programmationsTableHeader;
        programmationsTableWidget->setRowCount(tacheSimplePreemptive.pSize());
        programmationsTableWidget->setColumnCount(5);
        programmationsTableHeader << "Date de début" << "Horaire de début" << "Date de fin" << "Horaire de Fin" << "Pourcentage";
        programmationsTableWidget->setHorizontalHeaderLabels(programmationsTableHeader);
        programmationsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        programmationsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        programmationsTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        programmationsTableWidget->setGeometry(QApplication::desktop()->screenGeometry());
        int i = 0;
        for(TacheSimplePreemptive::p_const_iterator it = tacheSimplePreemptive.pBegin(); it != tacheSimplePreemptive.pEnd() ; ++it){
             programmationsTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString((*it)->getDateProgrammation().toString())));
             programmationsTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString((*it)->getHoraireProgrammation().toString())));
             programmationsTableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString((*it)->getDateFin().toString())));
             programmationsTableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString((*it)->getHoraireFin().toString())));
             std::stringstream str;
             str << (*it)->getPourcentage();
             programmationsTableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(str.str())));
             i++;
        }
    }
    vBox->addLayout(formlayout);
    if(vBoxPrecedence!=0){
        if(programmationsTableWidget != 0){
            vBoxPrecedence->addWidget(programmationsTableWidget);
        }
        vBox->addLayout(vBoxPrecedence);
    }
    else{
        if(programmationsTableWidget != 0){
            vBoxPrecedence = new QVBoxLayout();
            vBoxPrecedence->addWidget(programmationsTableWidget);
            vBox->addLayout(vBoxPrecedence);
        }
    }
    vBox->addLayout(hBoxOK);
}
