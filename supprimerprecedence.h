#ifndef SUPPRIMERPRECEDENCE_H
#define SUPPRIMERPRECEDENCE_H

# include <QWidget>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QDateEdit>
# include <QTimeEdit>
# include <QFormLayout>
# include <QPushButton>
# include "projet.h"
# include <QTreeWidget>
# include <QLabel>
# include <QCloseEvent>

class SupprimerPrecedence : public QWidget
{
    Q_OBJECT
protected:
    virtual void closeEvent(QCloseEvent *event);
private:
    Projet& nomProjet; // pour le nom de projet
    std::string * chemin; // pour le table de string de la première tâche
    unsigned int* tailleChemin; // pour la taille du tableau de string
    std::string titreTache; // pour le titre de la tâche
    std::string * chemin2; // pour le table de string de la première tâche
    unsigned int* tailleChemin2; // pour la taille du tableau de string
    std::string titreTache2; // pour le titre de la tâche
    QLabel *label;
    QTreeWidget * tree; // le tree-view
    QVBoxLayout* vBox; // pour harmoniser le tout
    QHBoxLayout* hBox1; // pour le Qlabel en haut
    QHBoxLayout* hBox2; // pour le widget central
    QHBoxLayout* hBox3; // pour le annuler / sauver
    QPushButton* annuler;  /*!< bouton annuler */
    QPushButton* sauver;  /*!< bouton sauver */
public:
    explicit SupprimerPrecedence(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent = 0);
    static void removeProjet(QList<QString>* chemin);
    void afficherTreeWidget(QTreeWidget* arbre, Element* element, QTreeWidgetItem * actuel=0);
public slots:
    void retourFenetrePrincipaleAnnuler();
    void retourFenetrePrincipaleSauver();
};

#endif // SUPPRIMERPRECEDENCE_H
