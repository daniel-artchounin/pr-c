#ifndef Horaire_H
#define Horaire_H
#include <iostream>
#include <iomanip>
#include <string>
#include "horaireexception.h"
#include "duree.h"

class Duree;
/*!
 * \class Horaire
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
     * \param h heure avec 0<=h<=23
     * \param m minute avec 0<=m<=59
     */
    Horaire(unsigned short int  h, unsigned short int  m):heure(h),minute(m) {
        if (h>23||m>59) throw HoraireException("erreur: initialisation horaire invalide");
    }

    /*!
     * \brief setHoraire
     * \param h heure avec 0<=h<=23
     * \param m minute avec 0<=m<=59
     */
    void setHoraire(unsigned short int h, unsigned short int m) {
        if (h>23||m>59) throw HoraireException("erreur: initialisation horaire invalide");
        heure=h;
        minute=m;
    }

    /*!
     * \brief afficher
     * Affiche l'horaire sous le format hhHmm
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
     * \brief soustraction permet de calculer le nombre de minutes séparant deux horaires (le résultat peut-être négatif)
     * \param horaire l'horaire à déduire de l'horaire de notre objet
     * \return le nombre de minutes entre les deux horaires : ce nombre peut volontairement etre négatif
     */
    int soustraction(const Horaire& horaire) const{
        return ( this->getHeure()- horaire.getHeure() )*60 + this->getMinute() - horaire.getMinute();
    }
};

/*!
 * \brief operator <<
 * Surcharge de l'opérateur <<
 * \param f ostream
 * \param h Horaire
 * \return ostream
 */
std::ostream& operator<<(std::ostream& f, const Horaire & h);

/*!
 * \brief operator - permet le nombre de minutes séparant deux horaires (le résultat peut-être négatif)
 * \param horaire1 le premier horaire
 * \param horaire2 le deuxième horaire
 * \return le nombre de minutes entre les deux horaires : ce nombre peut volontairement etre négatif
 */
int operator-(const Horaire& horaire1, const Horaire& horaire2);

#endif // Horaire_H
