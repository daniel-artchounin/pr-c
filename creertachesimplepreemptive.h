#ifndef CREERTACHESIMPLEPREEMPTIVE_H
#define CREERTACHESIMPLEPREEMPTIVE_H

# include <QWidget>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QFormLayout>
# include <QLineEdit>
# include <QDateEdit>
# include <QPushButton>
# include <QSpinBox>
# include <QLabel>
# include <QMessageBox>
# include "fenetreprincipale.h"
# include "creertache.h"

/*!
 * \class CreerTacheSimplePreemptive
 * \brief Classe contenant les champs permettant la création d'une tâche simple préemptive
 */
class CreerTacheSimplePreemptive : public CreerTache
{
    Q_OBJECT
protected :
    QHBoxLayout* hBox1; /*!< gestion de l'emplacement des champs pour les heures et les minutes*/
    QLabel* labelH; /*!< label : heures */
    QSpinBox *heures; /*!< durée : nombre d'heures */
    QLabel* labelM; /*!< label : minutes */
    QSpinBox *minutes; /*!< durée :  nombre de minutes */
public:

    /*!
     * \brief CreerTacheSimplePreemptive
     * Constructeur.
     * \param projet référence vers le nom du projet de la tâche à créer
     * \param chaine cheminement vers la tâche à créer
     * \param taille taille du tableau chaine
     * \param parent widget parent
     */
    explicit CreerTacheSimplePreemptive(Projet& projet, std::string * chaine, unsigned int* taille, QWidget *parent = 0);

signals:

public slots:

    /*!
     * \brief retourFenetrePrincipaleValider
     * Slot se déclenchant suite à la validation de l'utilisateur.
     * Permet d'enregistrer les données et de revenir à la fenetre principale.
     */
    void retourFenetrePrincipaleValider();
};
#endif // CREERTACHESIMPLEPREEMPTIVE_H
