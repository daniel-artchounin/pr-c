#ifndef FENETREGESTIONPROJET_H
#define FENETREGESTIONPROJET_H

#include <QWidget>
# include <projetmanager.h>
# include <QTreeWidget>
# include <QHBoxLayout>
# include <QMenu>
# include "creertachecomposite.h"
# include "creertachesimplepreemptive.h"
# include "creertachesimplenonpreemptive.h"

class CreerTacheSimplePreemptive;
class CreerTacheSimpleNonPreemptive;
class FenetreGestionProjet : public QWidget
{
    Q_OBJECT
private:
    QTreeWidget * tree;
    QHBoxLayout* hBox;
    QAction * monAction;
    QAction * creationTacheComposite;
    QAction * creationTacheSimplePreemptive;
    QAction * creationTacheSimpleNonPreemptive;
    CreerTacheComposite* creerTacheComposite;
    CreerTacheSimplePreemptive* creerTacheSimplePreemptive;
    CreerTacheSimpleNonPreemptive* creerTacheSimpleNonPreemptive;
public:
    explicit FenetreGestionProjet(QWidget *parent = 0);
    void afficherTreeWidget(unsigned int profondeur, ProjetManager& projetManager, QTreeWidget* arbre, QTreeWidgetItem * actuel=0, Element * element=0);
    QTreeWidget* getTree()const{
        return tree;
    }
signals:

public slots:
    void showContextMenu(const QPoint&);
    void test();
    void fenetreCreerTacheComposite();
    void fenetreCreerTacheSimplePreemptive();
    void fenetreCreerTacheSimpleNonPreemptive();
};

#endif // FENETREGESTIONPROJET_H
