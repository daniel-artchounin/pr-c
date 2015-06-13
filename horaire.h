#ifndef Horaire_H
#define Horaire_H
#include <iostream>
#include "duree.h"
#include "horaireexception.h"

/*! \class Horaire
 * \brief Classe permettant de manipuler des horaires
 * L'utilisation de cette classe nécessite des dates valides au sens commun du terme.
 * Déclenchement d'exception dans le cas contraire.
 */
class Horaire {

private:

    unsigned short int  heure; /*!< heure avec 0<=h<=23 */
    unsigned short int  minute; /*!< minute avec 0<=m<=59 */

public:

    /*!
     * \brief Constructeur
     * Crée un horaire à partir d'une heure et de minutes.
     * \param h heure avec 0<=h<=23
     * \param m minute avec 0<=m<=59
     */
    Horaire(unsigned short int  h, unsigned short int  m):heure(h),minute(m) {
        if (h>23||m>59) throw HoraireException("erreur: initialisation horaire invalide");
    }

    /*!
     * \brief Horaire
     * Crée un horaire à partir d'un string au format hhHmm.
     * \param horaire format hhHmm
     */
    Horaire(std::string horaire):heure(0),minute(0) {
        setHoraire(horaire);
    }

    /*!
     * \brief setHoraire
     * Modifie l'horaire selon l'heure et les minutes données.
     * \param h heure avec 0<=h<=23
     * \param m minute avec 0<=m<=59
     */
    void setHoraire(unsigned short int h, unsigned short int m) {
        if (h>23||m>59) throw HoraireException("erreur: initialisation horaire invalide");
        heure=h;
        minute=m;
    }

    /*!
     * \brief setHoraire
     * Modifie l'horaire selon le string au format hhHmm.
     * \param horaire string au format hhHmm
     */
    void setHoraire(std::string horaire);

    /*!
     * \brief afficher
     * Affiche l'horaire sous le format hhHmm.
     * \param f ostream
     */
    void afficher(std::ostream& f=std::cout) const {
        f<<std::setfill('0')<<std::setw(2)<<heure<<"H"<<std::setfill('0')<<std::setw(2)<<minute<<std::setfill(' ');
    }

    /*!
     * \brief getHeure
     * \return heure de l'Horaire
     */
    unsigned short int getHeure() const {
        return heure;
    }

    /*!
     * \brief getMinute
     * \return minute de l'Horaire
     */
    unsigned short int getMinute() const {
        return minute;    //<!Retourne les minutes de l'Horaire
    }

    /*!
     * \brief operator <
     * \param h Horaire
     * \return true si Horaire précède h dans le temps
     */
    bool operator<(const Horaire& h) const;

    /*!
     * \brief operator >
     * \param h Horaire
     * \return true si Horaire succède h dans le temps
     */
    bool operator>(const Horaire& h) const;

    /*!
     * \brief operator <=
     * \param h Horaire
     * \return true si Horaire inférieur ou égal à h dans le temps
     */
    bool operator<=(const Horaire& h) const;

    /*!
     * \brief operator >=
     * \param h Horaire
     * \return true si Horaire supérieur ou égal à h dans le temps
     */
    bool operator>=(const Horaire& h) const;

    /*!
     * \brief operator ==
     * \param h Horaire
     * \return true si Horaire est égal à h dans le temps
     */
    bool operator==(const Horaire& h) const;

    /*!
     * \brief formatHHMM
     * \return l'horaire au format hhmm
     */
    std::string formatHHMM() const;

    /*!
     * \brief Horaire::toString
     * \return horaire au format hhHmm
     */
    std::string toString() const;

    /*!
     * \brief addDuree
     * \param duree
     * \return un horaire après ajout de la durée
     */
    Horaire addDuree(const Duree duree) const;

    /*!
     * \brief soustraction
     * Permet de calculer le nombre de minutes séparant deux horaires (le résultat peut-être négatif).
     * \param horaire l'horaire à déduire de l'horaire de notre objet
     * \return le nombre de minutes entre les deux horaires : ce nombre peut volontairement etre négatif
     */
    int soustraction(const Horaire& horaire) const{
        return ( this->getHeure()- horaire.getHeure() )*60 + this->getMinute() - horaire.getMinute();
    }
};

/*!
 * \brief operator <<
 * Surcharge de l'opérateur <<.
 * \param f ostream
 * \param h Horaire
 * \return ostream
 */
std::ostream& operator<<(std::ostream& f, const Horaire & h);

/*!
 * \brief operator >>
 * Surcharde de l'opérateur >>.
 * \param flot istream
 * \param horaire Horaire
 * \return istream
 */
std::istream& operator>>(std::istream& flot, Horaire& horaire);

/*!
 * \brief operator
 * Permet d'obtenir le nombre de minutes séparant deux horaires (le résultat peut-être négatif).
 * \param horaire1 le premier horaire
 * \param horaire2 le deuxième horaire
 * \return le nombre de minutes entre les deux horaires : ce nombre peut volontairement etre négatif
 */
int operator-(const Horaire& horaire1, const Horaire& horaire2);

#endif // Horaire_H
