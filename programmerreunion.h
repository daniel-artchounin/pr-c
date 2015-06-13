#ifndef PROGRAMMERREUNION_H
#define PROGRAMMERREUNION_H

#include <QWidget>
#include "programmerevenement.h"

/*!
 * \brief ProgrammerReunion
 * Class permettant de créer un formulaire afin de créer ou modifier une programmation d'une réunion
 */
class ProgrammerReunion : public ProgrammerEvenement
{
    Q_OBJECT
public:

    /*!
     * \brief ProgrammerReunion
     * Crée le formulaire ProgrammerRendezVous.
     * \param parent
     */
    explicit ProgrammerReunion(QWidget *parent = 0);

    /*!
     * \brief ProgrammerReunion
     * Crée le formulaire ProgrammerRendezVous pré-rempli avec les données d'une programmation donnée.
     * \param prog
     * \param parent
     */
    explicit ProgrammerReunion(ProgrammationEvenement* prog, QWidget *parent = 0);

signals:

public slots:

    /*!
     * \brief retourFenetrePrincipaleValider
     * Permet de créer ou modifier la programmation si celle-ci a été donnée au moment de valider.
     */
    virtual void retourFenetrePrincipaleValider();
};

#endif // PROGRAMMERREUNION_H
