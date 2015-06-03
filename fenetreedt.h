#ifndef FENETREEDT_H
#define FENETREEDT_H

#include <QWidget>
#include <QGraphicsView>
#include "programmationmanager.h"
#include <QDate>
#include "date.h"
#include "tools.h"
#include "creerprogrammationevenement.h"

/*!
 * \class FenetreEDT
 * \brief Classe permettant de gérer l'interface de l'emploi du temps
 */
class FenetreEDT : public QGraphicsView
{
    Q_OBJECT

private:
    QGraphicsScene *scene; /*!< scene >*/
    QAction *progEvt;
    CreerProgrammationEvenement* creerProgEvt;
    int week;

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
     * Retourne la largeur d'un jour sur la grille
     * \return int
     */
    int getWidthDay();

    /*!
     * \brief getHeightHour
     * Retourne la hauteur d'une heure sur la grille
     * \return int
     */
    int getHeightHour();

    /*!
     * \brief toPositionX
     * Retourne la coordonnée x correspondant à la date donnée
     * \param date Date
     * \return int
     */
    int toPositionX(const Date& date);

    /*!
     * \brief toPositionY
     * Returne la coordonnée y  correspondant à l'horaire donnée
     * \param horaire Horaire
     * \return int
     */
    int toPositionY(const Horaire& horaire);

    /*!
     * \brief toHeight
     * Returne l'hauteur correspondant à la durée donnée
     * \param duree
     * \return int
     */
    int toHeight(const Duree& duree);

    /*!
     * \brief minX
     * Retourne la coordonnée x minimal afin de prendre en compte la bordure
     * \return int
     */
    int minX();

    /*!
     * \brief minY
     * Retourne la coordonée y minimal afin de prendre en compte l'entête
     * \return int
     */
    int minY();

    /*!
     * \brief maxY
     * Retourne la coordonée y maximal afin d'atteindre le bas de la grille
     * \return
     */
    int maxY();

    /*!
     * \brief toDay
     * Retourne le jour de la semaine correspondant à la date de donnée
     * Lundi = 1, ..., Dimance = 7
     * \param date Date
     * \return int
     */
    int toDay(const Date& date);

    /*!
     * \brief creerActions
     * Permet d'initialiser les actions
     */
    void creerActions();

public:
    /*!
     * \brief Contructeur
     * \param parent
     */
    explicit FenetreEDT(QWidget *parent = 0);

    /*!
     * \brief loadWeek
     * Permet d'afficher une semaine
     */
    void loadWeek();

    /*!
     * \brief drawProgrammation
     * Permet de représenter par un rectangle la programmation
     * \param ddebut Date de début
     * \param hdebut Horaire de début
     * \param dfin Date de fin
     * \param hfin Horaire de fin
     * \param duree Durée
     * \param brush Brush
     */
    void drawProgrammation(Date ddebut, Horaire hdebut, Date dfin, Horaire hfin, Duree duree, QBrush brush);

    void drawText(QPainter & painter, const QPointF & point, int flags, const QString & text, QRectF * boundingRect = 0);


signals:

public slots:
    /*!
     * \brief drawForeground
     * Permet d'afficher le fond.
     * \param painter
     * \param rect
     */
    void drawForeground(QPainter* painter, const QRectF& rect);

    void contextMenuEvent(QContextMenuEvent *event);

    void creerProgrammationEvenement();
};

#endif // FENETREEDT_H
