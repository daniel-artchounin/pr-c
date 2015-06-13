#include "informationstache.h"
# include "tache.h"
# include <QHeaderView>
# include <QApplication>
# include <QDesktopWidget>
InformationsTache::InformationsTache(const Tache& tache, QWidget *parent):
    InformationsElement(tache, parent)
{
    precendentTableWidget = 0;
    if(tache.tPSize() > 0){
        precendentTableWidget = new QTableWidget();
        QStringList precedentTableHeader;
        precendentTableWidget->setRowCount(tache.tPSize());
        precendentTableWidget->setColumnCount(1);
        precedentTableHeader << "Tâche(s) précédente(s)";
        precendentTableWidget->setHorizontalHeaderLabels(precedentTableHeader);
        precendentTableWidget->horizontalHeader()->setStretchLastSection(true);
        precendentTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        precendentTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        precendentTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        precendentTableWidget->setGeometry(QApplication::desktop()->screenGeometry());
        int i = 0;
        for(Tache::tp_const_iterator it = tache.tPBegin(); it != tache.tPEnd() ; ++it){
             precendentTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(it->first)));
             i++;
        }
    }
    suivantTableWidget = 0;
    if(tache.tSSize() > 0){
        suivantTableWidget = new QTableWidget();
        QStringList suivantTableHeader;
        suivantTableWidget->setRowCount(tache.tSSize());
        suivantTableWidget->setColumnCount(1);
        suivantTableHeader << "Tâche(s) suivante(s)";
        suivantTableWidget->setHorizontalHeaderLabels(suivantTableHeader);
        suivantTableWidget->horizontalHeader()->setStretchLastSection(true);
        suivantTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        suivantTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        suivantTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        suivantTableWidget->setGeometry(QApplication::desktop()->screenGeometry());
        int i = 0;
        for(Tache::ts_const_iterator it = tache.tSBegin(); it != tache.tSEnd() ; ++it){
             suivantTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(it->first)));
             i++;
        }
    }    
    vBoxPrecedence = 0;
    if(precendentTableWidget !=0 || suivantTableWidget!=0){
        vBoxPrecedence = new QVBoxLayout();
    }
    if(precendentTableWidget !=0){
        hBoxPrecedent = new QHBoxLayout();
        hBoxPrecedent->addWidget(precendentTableWidget);
        vBoxPrecedence->addLayout(hBoxPrecedent);
    }
    if(suivantTableWidget!=0){
        hBoxSuivant = new QHBoxLayout();
        hBoxSuivant->addWidget(suivantTableWidget);
        vBoxPrecedence->addLayout(hBoxSuivant);
    }
}
