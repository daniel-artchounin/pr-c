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
    Projet& nomProjet; // pour le nom de projet
    std::string * chemin; // pour le table de string de la première tâche
    unsigned int* tailleChemin; // pour la taille du tableau de string
    std::string titreTache; // pour le titre de la tâche
    std::string * chemin2; // pour le table de string de la première tâche
    unsigned int* tailleChemin2; // pour la taille du tableau de string
    std::string titreTache2; // pour le titre de la tâche
    QLabel *label;
    QHBoxLayout* hBox1; // pour le Qlabel en haut
    QHBoxLayout* hBox2; // pour le widget central    
public:
    explicit GestionPrecedence(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent = 0);
};

#endif // GESTIONPRECEDENCE_H
