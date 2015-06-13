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
# include "fenetreannulervalider.h"
# include "gestionprecedence.h"
# include <QListWidget>
# include <QListWidgetItem>

/*!
 * \class SupprimerPrecedence
 * \brief Classe permettant de supprimer une contrainte de précédence
 */
class SupprimerPrecedence : public GestionPrecedence
{
    Q_OBJECT

protected :

    QListWidget* listeDeTaches; /*!< contiendra la liste des tâches précédentes */

    /*!
     * \brief fromQStringListToStdStringArray
     * Méthode permettant de générer un tableau de string à partir d'un QStringList.
     * \param chemin la QStringList
     * \param taille la taille du tableau qui sera généré
     * \return tableau de string
     */
    std::string* fromQStringListToStdStringArray(QStringList chemin, unsigned int* taille);

    /*!
     * \brief afficherListeTacheWidget
     * Méthode permettant d'afficher la liste des tâches précédentes.
     */
    void afficherListeTacheWidget();

public:

    /*!
     * \brief SupprimerPrecedence
     * Constructeur.
     * \param projet référence vers le projet.
     * \param chaine tableau de chaine de caractères matérialisant le cheminement (ensemble des tâches composites)
     * \param taille la taille de chaine
     * \param titreT le titre de la tâche
     * \param parent le widget parent
     */
    explicit SupprimerPrecedence(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent = 0);

public slots:

    /*!
     * \brief retourFenetrePrincipaleValider
     * Slot se déclenchant suite à la validation de l'utilisateur.
     * Permet d'enregistrer les données et de revenir à la fenetre principale.
     */
    void retourFenetrePrincipaleValider();

};
#endif // SUPPRIMERPRECEDENCE_H
