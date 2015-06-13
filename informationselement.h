#ifndef INFORMATIONSELEMENT_H
#define INFORMATIONSELEMENT_H
# include "element.h"
# include <QPushButton>
# include <QHBoxLayout>
# include <QLabel>
# include <QWidget>
# include <QFormLayout>

/*!
 * \class InformationsElement
 * \brief Classe permettant d'afficher des informations sur un élément
 */
class InformationsElement : public QWidget
{
    Q_OBJECT
protected:

    QFormLayout* formlayout; /*!< formulaire ok */
    QPushButton* ok;  /*!< bouton ok */
    QHBoxLayout* hBoxOK; /*!< contient le bouton ok */
    QVBoxLayout* vBox; /*!< pour harmoniser */
    QLabel *titre; /*!< titre de la tâche */
    QLabel *dateDebut; /*!< date de disponibilité */
    QLabel *horaireDebut; /*!< horaire de disponibilité */
    QLabel *dateEcheance; /*!< date d'échéance */
    QLabel *heureEcheance; /*!< horaire d'échéance */
    QLabel *duree; /*!< durée de l'élément */

    /*!
     * \brief closeEvent
     * Permet de gérer la requête de fermeture du widget
     * \param event évènement
     */
    virtual void closeEvent(QCloseEvent *event);

public:

    /*!
     * \brief InformationsElement
     * Constructeur.
     * \param element référence vers l'élément nous intéressant
     * \param parent widget parent
     */
    explicit InformationsElement(const Element& element, QWidget *parent = 0);

signals:

public slots:

    void retourFenetrePrincipale();

};

#endif // INFORMATIONSELEMENT_H
