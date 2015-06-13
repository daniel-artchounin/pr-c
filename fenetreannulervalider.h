#ifndef FENETREANNULERVALIDER_H
#define FENETREANNULERVALIDER_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

/*!
 * \class FenetreAnnulerValider
 * \brief Classe abstraite contenant un bouton d'annulation et un bouton de validation
 */
class FenetreAnnulerValider : public QWidget
{
    Q_OBJECT

protected :

    QPushButton* valider;  /*!< bouton valider */
    QPushButton* annuler;  /*!< bouton annuler */
    QHBoxLayout* hBoxAnnulerValider;
    QVBoxLayout* vBox; // pour harmoniser le tout

    /*!
     * \brief closeEvent
     * Permet de gérer la requête de fermeture du widget.
     * \param event évènement
     */
    virtual void closeEvent(QCloseEvent *event);

public:

    /*!
     * \brief FenetreAnnulerValider
     * Constructeur.
     * \param parent widget parent
     */
    explicit FenetreAnnulerValider(QWidget *parent = 0);

signals:

public slots:

    /*!
     * \brief retourFenetrePrincipaleAnnuler
     * Slot permettant de gérer le click sur le bouton annuler->
     */
    void retourFenetrePrincipaleAnnuler();

    /*!
     * \brief retourFenetrePrincipaleValider
     * Méthode virtuelle pure.
     * Slot se déclenchant suite à la validation de l'utilisateur.
     * Permet d'enregistrer les données et de revenir à la fenetre principale.
     */
    virtual void retourFenetrePrincipaleValider()=0;
};

#endif // FENETREANNULERVALIDER_H
