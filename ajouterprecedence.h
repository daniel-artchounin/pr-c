#ifndef AJOUTERPRECEDENCE_H
#define AJOUTERPRECEDENCE_H

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
# include "fenetreannulervalider.h"
# include "gestionprecedence.h"

/*!
 * \class AjouterPrecedence
 * \brief Classe permettant d'ajouter une contrainte de précédence
 */
class AjouterPrecedence : public GestionPrecedence
{
    Q_OBJECT

protected:
    QTreeWidget * tree; /*!< tree view */
    /*!
     * \brief afficherTreeWidget
     * Permet d'afficher le tree view.
     * \param arbre pointeur sur un QTreeWidget
     * \param element élément "racine" de l'arborescence (un projet ou une tâche composite)
     * \param actuel l'élément auquel on souhaite ajoute des QTreeWidgetItem dans l'algorithme récursif (à négliger lors de l'appel de la méthode)
     */
    void afficherTreeWidget(QTreeWidget* arbre, Element* element, QTreeWidgetItem * actuel=0);

public:

    /*!
     * \brief removeProjet
     * Permet de retirer le titre du projet du cheminement.
     * \param chemin le cheminement
     */
    static void removeProjet(QList<QString>* chemin);

    /*!
     * \brief AjouterPrecedence
     * Constructeur.
     * \param projet référence vers le projet.
     * \param chaine tableau de chaine de caractères matérialisant le cheminement (ensemble des tâches composites)
     * \param taille la taille de chaine
     * \param titreT le titre de la tâche
     * \param parent le widget parent
     */
    explicit AjouterPrecedence(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent = 0);

signals:

public slots:

    /*!
     * \brief retourFenetrePrincipaleValider
     * slot se déclenchant suite à la validation de l'utilisateur
     * permet d'enregistrer les données
     * et de revenir à la fenetre principale
     */
    void retourFenetrePrincipaleValider();
};

#endif // AJOUTERPRECEDENCE_H
