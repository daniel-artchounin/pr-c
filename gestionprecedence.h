#ifndef GESTIONPRECEDENCE_H
#define GESTIONPRECEDENCE_H

# include "projet.h"
# include <QWidget>
# include <QLabel>
# include <QTreeWidget>
# include <QHBoxLayout>
# include <QTreeWidgetItem>
# include "fenetreannulervalider.h"

class GestionPrecedence : public FenetreAnnulerValider
{
protected:
    virtual void closeEvent(QCloseEvent *event);
public:   
    explicit GestionPrecedence(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent = 0);
    Projet& nomProjet; // pour le nom de projet
    std::string * chemin; // pour le table de string de la première tâche
    unsigned int* tailleChemin; // pour la taille du tableau de string
    std::string titreTache; // pour le titre de la tâche
    std::string * chemin2; // pour le table de string de la première tâche
    unsigned int* tailleChemin2; // pour la taille du tableau de string
    std::string titreTache2; // pour le titre de la tâche
    QLabel *label;
    QTreeWidget * tree; // le tree-view
    QHBoxLayout* hBox1; // pour le Qlabel en haut
    QHBoxLayout* hBox2; // pour le widget central
public:
    void afficherTreeWidget(QTreeWidget* arbre, Element* element, QTreeWidgetItem * actuel=0);
    static void removeProjet(QList<QString>* chemin);
};

#endif // GESTIONPRECEDENCE_H
