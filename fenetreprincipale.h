#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

# include "zonecentrale.h"
# include <tools.h>
# include <QToolBar>
# include <QMainWindow>
# include "creerprojet.h"

/*! \class FenetrePrincipale
 * \brief Classe servant de fenetre principale à l'application.
 * Design pattern singleton
 */
class ZoneCentrale;
class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT
protected :
    /*!
     * \brief closeEvent
     * Permet de gérer la requête de fermeture du widget
     * \param event évènement
     */
    virtual void closeEvent(QCloseEvent *event);
    /*!
     * \brief showEvent
     * Permet de gérer la requête d'affichage du widget
     * \param event évènement
     */
    void showEvent( QShowEvent* event );
private:
    ZoneCentrale* zoneCentrale; /*!< zone contrale de la fenêtre principale*/
    QMenu* menuGestion; /*!< menu gestion de la barre de menus */
    QMenu* menuFenetre; /*!< menu fenêtre de la barre de menus */
    QMenu* menuAide; /*!< menu aide de la barre de menus */
    QToolBar* barrreOutils; /*!< barre d'outils */
    QAction* actionSave; /*!< action permettant de sauver le travail */
    QAction* actionLoad; /*!< action permettant de sauver charger un fichier de données*/
    QAction* actionCreerProjet; /*!< action permettant de créer un projet */
    QAction* actionQuitter; /*!< action permettant de quitter l'application */
    QAction* actionPrevious; /*!< action permettant de passer à la semaine suivante */
    QAction* actionNext; /*!< action permettant de passer à la semaine précédente */
    QAction* actionExportSemaine; /*!< action permettant d'exporter une semaine */
    QAction* actionExportProjet; /*!< action permettant d'exporter un projet */
    QAction* actionEnregistrerProjet; /*!< action permettant d'enregistrer un projet */
    QAction* actionImporterProjet; /*!< action permettant d'importer un projet */
    CreerProjet* creerProjet; /*!< Pointeur vers la fenêtre de création de projet */
    bool dejaSauver; /*!< action permettant de savoir si l'on a déjà sauvegardé le travail en cours */

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

    /*!
     * \brief libererInstance
     * permet de libérer l'instance
     * méthode statique
     * design pattern singleton
     */
    static void libererInstance();

    /*!
     * \brief getInstance
     * permet de récupérer l'instance ou de la construire
     * méthode statique
     * design pattern singleton
     */
    static FenetrePrincipale& getInstance();

    /*!
     * \brief updateEDT
     * Permet de mettre à jour l'emploi du temps
     */
    void updateEDT();

    /*!
     * \brief getCreerActionProjet accesseur
     * \return pointeur sur l'action de création de projet
     */
    QAction* getCreerActionProjet(){
        return actionCreerProjet;
    }

    /*!
     * \brief getZoneCentrale accesseur
     * \return pointeur sur la zone centrale
     */
    ZoneCentrale* getZoneCentrale()const{
        return zoneCentrale;
    }

signals:

public slots:

    /*!
     * \brief chargerFichier
     * slot permettant de charger un fichier de données
     */
    void chargerFichier();

    /*!
     * \brief sauverFichier
     * slot permettant de sauvegarder le travail en cours
     */
    void sauverFichier();

    /*!
     * \brief fenetreCreerProjet
     * slot permettant de créer un projet
     */
    void fenetreCreerProjet();

    /*!
     * \brief goToPreviousWeek
     * Permet d'aller à la semaine précédente
     */
    void goToPreviousWeek();

    /*!
     * \brief goToNextWeek
     * Permet d'aller à la semaine suivante
     */
    void goToNextWeek();

    /*!
     * \brief exporterUneSemaine
     * Permet d'exporter la semaine afficher actuellement
     */
    void exporterUneSemaine();

    /*!
     * \brief exporterUnProjet
     * slot permettant d'exporte un projet
     */
    void exporterUnProjet();

    /*!
     * \brief enregistrerUnProjet
     * slot permettant d'enregistrer un projet
     */
    void enregistrerUnProjet();

    /*!
     * \brief chargerProjet
     * slot permettant de charger un projet
     */
    void chargerProjet();
};

#endif // FENETREPRINCIPALE_H
