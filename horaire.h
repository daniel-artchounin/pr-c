#ifndef Horaire_H
#define Horaire_H
#include <iostream>
#include <iomanip>
#include <QString>
#include "horaireexception.h"

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
     * \brief Horaire::toQString
     * \return horaire au format hhHmm
     */
    QString toQString() const;
};

/*!
 * \brief operator <<
 * Surcharge de l'opérateur <<
 * \param f ostream
 * \param h Horaire
 * \return ostream
 */
std::ostream& operator<<(std::ostream& f, const Horaire & h);

#endif // Horaire_H
