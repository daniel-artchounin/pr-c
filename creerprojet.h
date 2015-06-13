#ifndef CREERPROJET_H
#define CREERPROJET_H

#include <QWidget>
# include <QPushButton>
# include <QVBoxLayout>
# include <QDateEdit>
# include <QTimeEdit>
# include <QFormLayout>
# include <QLineEdit>
# include "creerprojettache.h"

/*! \class CreerProjet
 * \brief Classe contenant les champs permettant de créer un projet
 */
class CreerProjet : public CreerProjetTache
{
    Q_OBJECT
protected :

public:

    /*!
     * \brief CreerProjet
     * Constructeur.
     * \param parent widget parent
     */
    explicit CreerProjet(QWidget *parent = 0);

signals:

public slots:

    /*!
     * \brief retourFenetrePrincipaleValider
     * Slot se déclenchant suite à la validation de l'utilisateur.
     * Permet d'enregistrer les données et de revenir à la fenetre principale.
     */
    void retourFenetrePrincipaleValider();
};

#endif // CREERPROJET_H
