#ifndef MODIFIERPROGRAMMATIONEVENEMENT_H
#define MODIFIERPROGRAMMATIONEVENEMENT_H

#include <QListWidget>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include "fenetreannulervalider.h"

/*!
 * \brief EditerProgrammation
 * Classe permettant de modifier ou supprimer les programmations.
 */
class EditerProgrammation : public QWidget {
    Q_OBJECT

protected :

    QListWidget* list; /*!< list contenant les différentes programmations */
    QHBoxLayout* hBox; /*!< hBox */
    QHBoxLayout* hBoxButon; /*!< hBoxButon contenant les QPushButton */
    QVBoxLayout* vBox; /*!< vBox */
    QPushButton* select; /*!< select bouton permettant de sélectionner une programmation */
    QPushButton* suppr; /*!< suppr bouton permettant de supprimer la programmation sélectionner dans la liste */
    FenetreAnnulerValider* form; /*!< form */

public:

    /*!
     * \brief EditerProgrammation
     * Crée l'interface d'édition des programmations existantes (suppressions et modifications)
     * \param parent widget parent
     */
    explicit EditerProgrammation(QWidget *parent = 0);

    /*!
     * \brief updateListe
     * Met à jour la liste des programmations affichée
     */
    void updateListe();

signals:

public slots:

    /*!
     * \brief closeEvent
     * Permet de gérer la requête de fermeture du widget
     * \param event évènement
     */
    void closeEvent(QCloseEvent *event);

    /*!
     * \brief selectionner
     * Gère l'action de sélection dans la liste via le bouton sélectionner
     */
    void selectionner();

    /*!
     * \brief supprimer
     * Gère l'action de suppresion via la bouton supprimer
     */
    void supprimer();
};

#endif // MODIFIERPROGRAMMATIONEVENEMENT_H
