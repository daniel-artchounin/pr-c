#ifndef DATETIME_H
#define DATETIME_H
#include "duree.h"
#include "horaire.h"

/*! \class Date
 * \brief Classe permettant de manipuler des dates standards
 * L'utilisation de cette classe nécessite des dates valides au sens commun du terme.
 * Déclenchement d'exception dans le cas contraire.
 */
class Date {

private:

    unsigned short int jour; /*!< jour entre 1 et 31*/
    unsigned short int mois; /*!< mois entre 1 et */
    unsigned int annee; /*!< année */

public:

    /*!
     * \brief Constructeur
     * Crée une date à partir d'un jour, un mois et une année.
     * \param j jour avec 1<=j<=31
     * \param m mois avec 1<=m<=12
     * \param a année avec a>=0
     */
    Date(unsigned int short j=1, unsigned int short m=1, unsigned int a=0):jour(1),mois(1),annee(0) {
        setDate(j,m,a);
    }

    /*!
     * \brief Constructeur
     * Permet de créer une date depuis un string au format jj/mm/aaaa.
     * \param date string au format jj/mm/aaaa
     */
    Date(std::string date):jour(1),mois(1),annee(0) {
        setDate(date);
    }

    /*!
     * \brief Constructeur de recopie.
     * \param date référence const vers une date
     */
    Date(const Date& date):jour(date.jour),mois(date.mois),annee(date.annee) {}

    /*!
     * \brief getJour
     * \return jour de la date
     */
    unsigned short int  getJour() const {
        return jour;
    }

    /*!
     * \brief getMois
     * \return mois de la date
     */
    unsigned short int  getMois() const {
        return mois;
    }

    /*!
     * \brief getAnnee
     * \return année de la date
     */
    unsigned int getAnnee() const {
        return annee;
    }

    /*!
     * \brief setDate
     * Modifie la date selon le jour, le mois et l'année donnés.
     * \param j jour avec 1<=j<=31
     * \param m mois avec 1<=m<=12
     * \param a année avec a>=0
     */
    void setDate(unsigned short int j, unsigned short int m, unsigned int a);

    /*!
     * \brief setDate
     * Modifie la date par celle représenté par le string donné.
     * Celui-ci doit être au format jj/mm/aaaa.
     * \param date string format jj/mm/aaaa
     */
    void setDate(std::string date);

    /*!
     * \brief setDateAujourdhui
     * Initilisation de la date avec la date d'aujourd'hui.
     */
    void setDateAujourdhui();

    /*!
     * \brief afficher
     * Affiche la date sous le format jj/mm/aaaa.
     * \param f ostream
     */
    void afficher(std::ostream& f=std::cout) const;

    /*!
     * \brief operator ==
     * \param d Date
     * \return true si les deux dates sont égales, false sinon
     */
    bool operator==(const Date& d) const;

    /*!
     * \brief operator <
     * \param d Date
     * \return true si d1 est avant d2, false sinon
     */
    bool operator<(const Date& d) const;

    /*!
     * \brief operator >
     * \param d Date
     * \return true si Date succède d dans le temps
     */
    bool operator>(const Date& d) const;

    /*!
     * \brief operator <=
     * \param d Date
     * \return true si Date inférieur ou égal à d dans le temps
     */
    bool operator<=(const Date& d) const ;

    /*!
     * \brief operator >=
     * \param d Date
     * \return true si Date supérieur ou égal à d dans le temps
     */
    bool operator>=(const Date& d) const;

    /*!
     * \brief demain
     * \return date du jour suivant
     */
    Date demain() const;

    /*!
     * \brief operator +
     * \param nb nombre de jour
     * \return la date après avoir ajouté nb à la date actuelle
     */
    Date operator+(unsigned int nb) const;

    /*!
     * \brief formatAAAAMMJJ
     * \return la date au format aaaammjj
     */
    std::string formatAAAAMMJJ() const;

    /*!
     * \brief toString
     * \return la date au format jj/mm/aaaa
     */
    std::string toString() const;

    /*!
     * \brief addDuree
     * Retourne la date obtenu après ajout de la durée à la date actuelle à partir de l'horaire donné.
     * \param duree
     * \param horaire
     * \return date
     */
    Date addDuree(const Duree duree, const Horaire horaire) const;
};

/*!
 * \brief operator <<
 * Surcharge de l'opérateur <<.
 * \param f ostream
 * \param x Date
 * \return ostream
 */
std::ostream& operator<<(std::ostream& f, const Date& x);

/*!
 * \brief operator >>
 * Surcharge de l'opérateur >>.
 * Lecture de la date au format jj/mm/aaaa.
 * \param flot istream
 * \param date Date
 * \return istream
 */
std::istream& operator>>(std::istream& flot, Date& date);

/*!
 * \brief operator -
 * \param d
 * \return nombre de jours séparant les deux dates
 */
int operator-(const Date& d1, const Date&d2 );

#endif // DATETIME_H
