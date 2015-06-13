#ifndef PROGRAMMERTACHESIMPLENONPREEMPTIVE_H
#define PROGRAMMERTACHESIMPLENONPREEMPTIVE_H

# include <QWidget>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QDateEdit>
# include <QTimeEdit>
# include <QFormLayout>
# include <QPushButton>
# include <projet.h>
# include "programmertachesimple.h"
#include "programmationtachesimplenonpreemptive.h"

/*!
 * \class ProgrammerTacheSimpleNonPreemptive
 * \brief Classe contenant les champs permettant de programmer une tâche simple non préemptive
 */
class ProgrammerTacheSimpleNonPreemptive : public ProgrammerTacheSimple
{
    Q_OBJECT
public:

    /*!
     * \brief ProgrammerTacheSimpleNonPreemptive
     * Constructeur.
     * \param projet pointeur vers le projet de la tâche à programmer
     * \param chaine cheminement vers la tâche à programmer
     * \param taille taille du tableau chemin
     * \param titreT titre de la tâche à programmer
     * \param parent widget parent
     */
    explicit ProgrammerTacheSimpleNonPreemptive(Projet* projet, std::string * chaine, unsigned int* taille, std::string& titreT, QWidget *parent = 0);

    /*!
     * \brief Constructeur
     * Crée un formulaire pré-rempli avec les données de la programmation
     * \param prog programmation à modifier
     * \param parent widget parent
     */
    explicit ProgrammerTacheSimpleNonPreemptive(ProgrammationTacheSimpleNonPreemptive* prog, QWidget *parent = 0);
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

#endif // PROGRAMMERTACHESIMPLENONPREEMPTIVE_H
