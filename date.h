#ifndef DATETIME_H
#define DATETIME_H
#include <iostream>
#include <QString>
#include "duree.h"

/*! \class Date
   * \brief Classe permettant de manipuler des dates standards
   *
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
     * \param j jour avec 1<=j<=31
     * \param m mois avec 1<=m<=12
     * \param a année avec a>=0
     */
    Date(unsigned int short j=1, unsigned int short m=1, unsigned int a=0):jour(1),mois(1),annee(0) {
        setDate(j,m,a);
    }
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
     * \param j jour avec 1<=j<=31
     * \param m mois avec 1<=m<=12
     * \param a année avec a>=0
     */
    void setDate(unsigned short int j, unsigned short int m, unsigned int a);
    /*!
     * \brief setDateAujourdhui
     * Initilisation de la date avec la date d'aujourd'hui
     */
    void setDateAujourdhui();
    /*!
     * \brief afficher
     * Affiche la date sous le format jj/mm/aaaa
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
     * \brief operator -
     * \param d
     * \return nombre de jours séparant les deux dates
     */
    int operator-(const Date& d) const;
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
     * \brief toQString
     * \return la date au format jj/mm/aaaa
     */
    QString toQString() const;
    /*!
     * \brief addDuree
     * Ajoute duree donnée en paramètre si celle-ci est supérieur à 24h
     * \param duree
     * \return date après ajout ou la même si durée inférieur à 24h
     */
    Date addDuree(const Duree duree);
};

/*!
 * \brief operator <<
 * Surcharge de l'opérateur <<
 * \param f ostream
 * \param x Date
 * \return ostream
 */
std::ostream& operator<<(std::ostream& f, const Date& x);

/*!
 * \brief operator >>
 * Surcharge de l'opératuer >>
 * Lecture de la date au format JJ/MM/AAAA
 * \param flot istream
 * \param date Date
 * \return istream
 */
std::istream& operator>>(std::istream& flot, Date& date);


#endif // DATETIME_H
