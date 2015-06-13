#ifndef PROGRAMMERRENDEZVOUS_H
#define PROGRAMMERRENDEZVOUS_H

#include <QWidget>
#include "programmerevenement.h"

/*!
 * \brief ProgrammerRendezVous
 * Class permettant de créer un formulaire afin de créer ou modifier une programmation d'un rendez vous
 */
class ProgrammerRendezVous : public ProgrammerEvenement
{
    Q_OBJECT
public:

    /*!
     * \brief ProgrammerRendezVous
     * Crée le formulaire ProgrammerRendezVous.
     * \param parent
     */
    explicit ProgrammerRendezVous(QWidget *parent = 0);

    /*!
     * \brief ProgrammerRendezVous
     * Crée le formulaire ProgrammerRendezVous pré-rempli avec les données d'une programmation donnée.
     * \param prog
     * \param parent
     */
    explicit ProgrammerRendezVous(ProgrammationEvenement* prog, QWidget *parent = 0);

signals:

public slots:

    /*!
     * \brief retourFenetrePrincipaleValider
     * Permet de créer ou modifier la programmation si celle-ci a été donnée au moment de valider.
     */
    virtual void retourFenetrePrincipaleValider();
};

#endif // PROGRAMMERRENDEZVOUS_H
