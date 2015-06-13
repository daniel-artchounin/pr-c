#ifndef FENETREEDT_H
#define FENETREEDT_H

#include <QWidget>
#include <QGraphicsView>
#include "manager.h"
#include "programmationmanager.h"
#include <QDate>
#include "date.h"
#include "tools.h"
#include "horaire.h"
#include "programmerreunion.h"
#include "programmerrendezvous.h"
#include "editerprogrammation.h"
#include <QMouseEvent>
#include <QGraphicsItem>
#include <iostream>

/*!
 * \class FenetreEDT
 * \brief Classe permettant de gérer l'interface de l'emploi du temps
 */
class FenetreEDT : public QGraphicsView
{
    Q_OBJECT

private:

    QGraphicsScene *scene; /*!< scene >*/
    QAction *actionProgRendezVous; /*!< actionProgRendezVous >*/
    QAction *actionProgReunion; /*!< actionProgReunion >*/
    QAction *actionEditProg; /*!< actionEditProg >*/
    ProgrammerRendezVous* progRdv; /*!< progRdv >*/
    ProgrammerReunion* progReunion; /*!< progReunion >*/
    EditerProgrammation* editProg; /*!< editProg >*/
    int week; /*!< week >*/

    /*!
     * \brief weekBegining
     * \return Date premier jour de la semaine actuelle
     */
    Date weekBegining();

    /*!
     * \brief weekEnd
     * \return Date dernier jour de la semaine actuelle
     */
    Date weekEnd();

    /*!
     * \brief getWidthDay
     * Retourne la largeur d'un jour sur la grille.
     * \return int
     */
    int getWidthDay();

    /*!
     * \brief getHeightHour
     * Retourne la hauteur d'une heure sur la grille.
     * \return int
     */
    int getHeightHour();

    /*!
     * \brief toPositionX
     * Retourne la coordonnée x correspondant à la date donnée.
     * \param date Date
     * \return int
     */
    int toPositionX(const Date& date);

    /*!
     * \brief toPositionY
     * Returne la coordonnée y  correspondant à l'horaire donnée.
     * \param horaire Horaire
     * \return int
     */
    int toPositionY(const Horaire& horaire);

    /*!
     * \brief toHeight
     * Returne l'hauteur correspondant à la durée donnée.
     * \param duree
     * \return int
     */
    int toHeight(const Duree& duree);

    /*!
     * \brief minX
     * Retourne la coordonnée x minimal afin de prendre en compte la bordure.
     * \return int
     */
    int minX();

    /*!
     * \brief minY
     * Retourne la coordonée y minimal afin de prendre en compte l'entête.
     * \return int
     */
    int minY();

    /*!
     * \brief maxY
     * Retourne la coordonée y maximal afin d'atteindre le bas de la grille.
     * \return int
     */
    int maxY();

    /*!
     * \brief dayOfWeek
     * Retourne le jour de la semaine correspondant à la date de donnée.
     * Lundi = 1, ..., Dimance = 7.
     * \param date Date
     * \return int
     */
    int dayOfWeek(const Date& date);

    /*!
     * \brief creerActions
     * Permet d'initialiser les actions.
     */
    void creerActions();

    /*!
     * \brief masquerFenetrePrincipal
     * Permet de masquer la fenêtre principale.
     */
    void masquerFenetrePrincipale();

    /*!
     * \brief drawProgrammation
     * Permet de représenter par un rectangle la programmation.
     * \param ddebut Date de début
     * \param hdebut Horaire de début
     * \param dfin Date de fin
     * \param hfin Horaire de fin
     * \param duree Durée
     */
    void drawProgrammation(std::string titre, Date ddebut, Horaire hdebut, Date dfin, Horaire hfin, Duree duree);

    /*!
     * \brief drawText
     * Permet d'afficher un text à une position donnée par un QPointF.
     * \param painter
     * \param point
     * \param flags
     * \param text
     * \param boundingRect
     */
    void drawText(QPainter & painter, const QPointF & point, int flags, const QString & text, QRectF * boundingRect = 0);

    /*!
     * \brief drawDates
     * Affiche les dates de la semaine.
     */
    void drawDates();

    /*!
     * \brief drawNames
     * Affiche un titre à une position représentée par des coordonnées x et y.
     * \param titre
     * \param x coordonnée x
     * \param y coordonnée y
     */
    void drawNames(std::string titre, int x, int y);

public:

    /*!
     * \brief Contructeur
     * Crée une FenetreEDT.
     * \param parent
     */
    explicit FenetreEDT(QWidget *parent = 0);

    /*!
     * \brief loadWeek
     * Permet d'afficher une semaine.
     */
    void loadWeek();

    /*!
     * \brief goToPreviousWeek
     * Permet d'afficher la semaine précédente.
     */
    void goToPreviousWeek() {
        week--;
        loadWeek();
    }

    /*!
     * \brief goToNextWeek
     * Permet d'afficher la semaine suivante.
     */
    void goToNextWeek() {
        week++;
        loadWeek();
    }

signals:

public slots:
    /*!
     * \brief drawForeground
     * Permet d'afficher le fond.
     * \param painter
     * \param rect
     */
    void drawBackground(QPainter* painter, const QRectF& rect);

    /*!
     * \brief contextMenuEvent
     * Affiche le menu contextuel sur un clique droit.
     * \param event
     */
    void contextMenuEvent(QContextMenuEvent *event);

    /*!
     * \brief programmerRendezVous
     * Affiche l'interface permettant de programmer un rendez vous.
     */
    void programmerRendezVous();

    /*!
     * \brief programmerReunion
     * Affiche l'interface permettant de programmer une réunion.
     */
    void programmerReunion();

    /*!
     * \brief editerProgrammation
     * Affiche l'interface permettant d'éditer une programmation.
     */
    void editerProgrammation();

    /*!
     * \brief saveWeek
     * Permet d'exporter au format xml la semaine actuelle dans le fichier donné.
     * \param file
     */
    void saveWeek(const QString& file);
};

#endif // FENETREEDT_H
