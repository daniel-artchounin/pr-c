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
# include "programmertachesimplenonpreemptive.h"
# include "programmertachesimplepreemptive.h"
# include "ajouterprecedence.h"
# include "supprimerprecedence.h"
# include <string>
# include <stdexcept>


class CreerTacheComposite;
class CreerTacheSimplePreemptive;
class CreerTacheSimpleNonPreemptive;
class FenetreGestionProjet : public QWidget
{
    Q_OBJECT
private:
    QTreeWidget * tree;
    QHBoxLayout* hBox;
    QAction * creationTacheComposite;
    QAction * creationTacheSimplePreemptive;
    QAction * creationTacheSimpleNonPreemptive;
    QAction * programmationTacheSimplePreemptive;
    QAction * programmationTacheSimpleNonPreemptive;
    QAction * supprimerProjet;
    QAction * ajouterPrecedence;
    QAction * supprimerPrecedence;
    CreerTacheComposite* creerTacheComposite;
    CreerTacheSimplePreemptive* creerTacheSimplePreemptive;
    CreerTacheSimpleNonPreemptive* creerTacheSimpleNonPreemptive;
    ProgrammerTacheSimplePreemptive* programmerTacheSimplePreemptive;
    ProgrammerTacheSimpleNonPreemptive* programmerTacheSimpleNonPreemptive;
    AjouterPrecedence* ajoutPrecedence;
    SupprimerPrecedence* suppressionPrecedence;
protected :
    // récupération du projet et gestion du cas d'erreur
    Projet& getAndRemoveProjet(QList<QString>* chemin);
public:
    explicit FenetreGestionProjet(QWidget *parent = 0);
    void afficherTreeWidget(unsigned int profondeur, ProjetManager& projetManager, QTreeWidget* arbre, QTreeWidgetItem * actuel=0, Element * element=0);
    QTreeWidget* getTree()const{
        return tree;
    }
    static QList<QString> getCheminement(QTreeWidgetItem * actuel);
    static void removeTache(QList<QString>* chemin);
    static std::string getNomTacheStd(QList<QString> chemin);
    static std::string getNomTacheAndRemoveTache(QList<QString>* chemin);
    static std::string* recupCheminDepuisProjet(QList<QString> chemin, unsigned int * taille);
signals:

public slots:
    void showContextMenu(const QPoint&);
    void test();
    void fenetreCreerTacheComposite();
    void fenetreCreerTacheSimplePreemptive();
    void fenetreCreerTacheSimpleNonPreemptive();
    void fenetreProgrammerTacheSimplePreemptive();
    void fenetreProgrammerTacheSimpleNonPreemptive();
    void fenetreAjouterPrecedence();
    void fenetreSupprimerPrecedence();
    void supprimerUnProjet();
};

#endif // FENETREGESTIONPROJET_H
