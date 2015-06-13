#ifndef GESTIONPRECEDENCE_H
#define GESTIONPRECEDENCE_H

# include "projet.h"
# include <QWidget>
# include <QLabel>
# include <QTreeWidget>
# include <QHBoxLayout>
# include <QTreeWidgetItem>
# include "fenetreannulervalider.h"

/*!
 * \class GestionPrecedence
 * \brief Classe abstraite contenant les champs permettant de gérer les contraintes de précédence
 */
class GestionPrecedence : public FenetreAnnulerValider
{
protected:

    /*!
     * \brief closeEvent
     * Permet de gérer la requête de fermeture du widget.
     * \param event évènement
     */
    virtual void closeEvent(QCloseEvent *event);

    Projet& nomProjet; /*!< le nom de projet */
    std::string * chemin; /*!< le tableau de string de la première tâche */
    unsigned int* tailleChemin;  /*!< la taille du tableau 1 de string */
    std::string titreTache; /*!< le titre de la tâche 1*/
    std::string * chemin2; /*!< le tableau de string de la deuxième tâche */
    unsigned int* tailleChemin2; /*!< la taille du tableau 2 de string */
    std::string titreTache2; /*!< le titre de la tâche 2 */
    QLabel *label; /*!< contiendra les informations sur l'interface */
    QHBoxLayout* hBox1; /*!< pour le Qlabel en haut */
    QHBoxLayout* hBox2; /*!< pour le widget central */

public:

    /*!
     * \brief GestionPrecedence Constructeur.
     * \param projet référence vers le projet
     * \param chaine tableau de string contenant le cheminement pour acccéder à la tâche dont on souhaite gérer les contrainte de précédence
     * \param taille taille du tableau chaine
     * \param titreT le titre de la tâche
     * \param parent widget parent
     */
    explicit GestionPrecedence(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent = 0);
};

#endif // GESTIONPRECEDENCE_H
