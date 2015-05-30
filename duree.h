#ifndef DUREE_H
#define DUREE_H
#include <iostream>
#include <iomanip>
#include "dureeexception.h"
#include <string>
#include "date.h"
#include "horaire.h"

class Horaire;
class Date;
/*! \class Duree
 * \brief Classe permettant de manipuler des durees
 * L'utilisation de cette classe nécessite des dates valides au sens commun du terme.
 * Déclenchement d'exception dans le cas contraire
*/
class Duree {
private:
    unsigned int nb_minutes; /*!< nombre de minutes avec nb_minutes >=0 */


public:
    /*!
     * \brief Constructeur
     * \param h heure avec h>=0
     * \param m minute avec 0<=m<=59
     */
    Duree(unsigned int h, unsigned int m):nb_minutes(h*60+m) {
        if (m>59) throw DureeException("erreur: initialisation duree invalide");
    }

    /*!
     * \brief Contructeur
     * \param m minute avec m>=0
     */
    Duree(unsigned int m=0):nb_minutes(m) {}

    /*!
     * \brief setDuree
     * \param heures heures>=
     * \param minutes 0<=minutes<=59
     */
    void setDuree(unsigned int heures, unsigned int minutes) {
        if (minutes>59) throw DureeException("erreur: initialisation duree invalide");
        nb_minutes=heures*60+minutes;
    }
    /*!
     * \brief getDureeEnMinutes
     * \return duree en minute
     */
    unsigned int getDureeEnMinutes() const {
        return nb_minutes;
    }
    /*!
     * \brief getDureeEnHeures
     * \return duree en heure
     */
    double getDureeEnHeures() const {
        return double(nb_minutes)/60;
    }
    /*!
     * \brief afficher
     * Affiche la duree sous le format hhHmm
     * \param f ostream
     */
    void afficher(std::ostream& f=std::cout) const {
        f<<std::setfill('0')<<std::setw(2)<<nb_minutes/60<<"H"<<std::setw(2)<<nb_minutes%60<<std::setfill(' ');
    }

    /*!
     * \brief toString
     * \return duree au format hhHmm
     */
    std::string toString() const;

    /*!
     * \brief estPlusPetitQue
     * \param b duree à comparer
     * \return true si duree est inférieur à b, false sinon
     */
    bool estPlusPetitQue(const Duree&b)const{
        return this->nb_minutes < b.nb_minutes;
    }

    /*!
     * \brief getMinute
     * \return partie minute
     */
    unsigned int getMinute() const {
        return nb_minutes%60;
    }

    /*!
     * \brief getHeure
     * \return partie heure
     */
    unsigned int getHeure() const {
        return nb_minutes/60;
    }

    /**
     * \brief addition permet d'additionner une date à la date de notre objet et de retourner
     * le résultat
     * \param dureeBis la durée à ajouter
     * \return le résultat de l'addition
     */
    Duree addition(const Duree & dureeBis)const{
        return Duree(getDureeEnMinutes()+dureeBis.getDureeEnMinutes());
    }
};

/*!
 * \brief operator <<
 * \param f
 * \param d
 * \return
 */
std::ostream& operator<<(std::ostream& f, const Duree & d);

/*!
 * \brief operator >>
 * Surcharge de l'opérateur >>
 * Lecture de la durée au format hhHmm
 * \param flot istream
 * \param duree Duree
 * \return istream
 */
std::istream& operator>>(std::istream& flot, Duree& duree); //lecture format

/*!
 * \brief operator <
 * \param a duree
 * \param b duree
 * \return booleen
 */
bool operator<(const Duree& a, const Duree&b);

/*!
 * \brief operator >
 * \param a duree
 * \param b duree
 * \return booleen
 */
bool operator>(const Duree& a, const Duree&b);

/*!
 * \brief operator <=
 * \param a duree
 * \param b duree
 * \return booleen
 */
bool operator<=(const Duree& a, const Duree&b);

/*!
 * \brief operator >=
 * \param a duree
 * \param b duree
 * \return booléen
 */
bool operator>=(const Duree& a, const Duree&b);

/*!
 * \brief operator +
 * \param duree1 duree
 * \param duree2 duree
 * \return résultat (Duree)
 */
Duree operator+(const Duree& duree1, const Duree& duree2);

#endif // DUREE_H
