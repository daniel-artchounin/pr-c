#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include "zonecentrale.h"
# include <tools.h>
# include <QToolBar>
# include <QMainWindow>
# include "creerprojet.h"

class ZoneCentrale;
class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT
protected :
    // This event handler is called with the given event when Qt receives a window close
    // request for a top-level widget from the window system.
    virtual void closeEvent(QCloseEvent *event);
    void showEvent( QShowEvent* event );
private:
    ZoneCentrale* zoneCentrale;
    QMenu* menuGestion;
    QMenu* menuFenetre;
    QMenu* menuAide;
    QToolBar* barrreOutils;
    QAction* actionSave;
    QAction* actionLoad;
    QAction* actionCreerProjet;
    QAction* actionQuitter;
    QAction* actionPrevious;
    QAction* actionNext;
    CreerProjet* creerProjet;
    bool dejaSauver;

    static FenetrePrincipale * instance; /*!< instance unique de FenetrePrincipale */

    /*!
     * \brief Constructeur
     * Constructeur privé afin d'empêcher la duplication
     */
    explicit FenetrePrincipale(QWidget *parent = 0);

    /*!
     *\brief Destructeur
     * Destructeur privé
     */
    ~FenetrePrincipale() {
        // std::cout << "je suis détruite" << std::endl ; // -> test
    }

    /*!
     * \brief Contructeur par recopie
     * Constructeur par recopie privé
     * \param fp FenetrePrincipale
     */
    FenetrePrincipale(const FenetrePrincipale& fp);

    /*!
     * \brief Operateur d'affectation
     * Opérateur d'affectation privé
     * \param fp FenetrePrincipale
     */
    FenetrePrincipale& operator=(const FenetrePrincipale& fp);

public:

    static void libererInstance();
    static FenetrePrincipale& getInstance();

signals:

public slots:
    void chargerFichier();
    void sauverFichier();
    void fenetreCreerProjet();
    void goToPreviousWeek();
    void goToNextWeek();
};

#endif // FENETREPRINCIPALE_H
