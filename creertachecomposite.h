#ifndef CREERTACHECOMPOSITE_H
#define CREERTACHECOMPOSITE_H

# include <QWidget>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QFormLayout>
# include <QLineEdit>
# include <QDateEdit>
# include <QPushButton>
# include <QCloseEvent>
# include "fenetreprincipale.h"
# include <QList>
# include <QString>
# include "creertache.h"

/*!
 * \class CreerTacheComposite
 * \brief Classe contenant les champs permettant la création d'une tâche composite
 */
class CreerTacheComposite : public CreerTache
{
    Q_OBJECT

protected :

public:

    /*!
     * \brief CreerTacheComposite
     * Constructeur.
     * \param projet référence vers le nom du projet de la tâche à créer
     * \param chaine cheminement vers la tâche à créer
     * \param taille taille du tableau chaine
     * \param parent widget parent
     */
    explicit CreerTacheComposite(Projet& projet, std::string * chaine, unsigned int* taille, QWidget *parent = 0);

signals:

public slots:

    /*!
     * \brief retourFenetrePrincipaleValider
     * Slot se déclenchant suite à la validation de l'utilisateur.
     * Permet d'enregistrer les données et de revenir à la fenetre principale.
     */
    void retourFenetrePrincipaleValider();
};

#endif // CREERTACHECOMPOSITE_H
