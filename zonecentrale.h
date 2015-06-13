#ifndef ZONECENTRALE_H
#define ZONECENTRALE_H
#include <QTabWidget>
# include "fenetregestionprojet.h"
# include "fenetreedt.h"
# include <QWidget>

/*! \class ZoneCentrale
 * \brief Classe étant la zone centrale de la fenetre principale de l'application.
 */
class FenetreGestionProjet;
class ZoneCentrale : public QWidget
{
    Q_OBJECT

private:

    FenetreEDT* fenetreEDT; /*!< pointeur vers l'interface de gestion de l'emloi du temps */
    FenetreGestionProjet* fenetreGestionProjet; /*!< pointeur vers l'interface de gestion de projet */
    QHBoxLayout* hBox; /*!< QHBoxLayout horizonatal pour l'affichage des deux interfaces */

public:

    /*!
     * \brief ZoneCentrale
     * Constructeur.
     * \param parent widget parent
     */
    explicit ZoneCentrale(QWidget *parent = 0);

    /*!
     * \brief getFenetreGestionProjet
     * Accesseur.
     * \return pointeur vers l'interface de gestion de projet
     */
    FenetreGestionProjet* getFenetreGestionProjet()const{
        return fenetreGestionProjet;
    }

    /*!
     * \brief getFenetreEDT
     * Accesseur.
     * \return pointeur vers l'interface de l'emploi du temps
     */
    FenetreEDT* getFenetreEDT()const{
        return fenetreEDT;
    }

signals:

public slots:

};

#endif // ZONECENTRALE_H
