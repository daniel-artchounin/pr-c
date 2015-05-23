#ifndef REUNION_H
#define REUNION_H
#include "evenement.h"
#include <string>

/*! \class Reunion
   * \brief Classe permettant de manipuler une réunion en définissant un lieu et un motif. Hérite de la classe Evenement.
   */
class Reunion : public Evenement
{
protected:
    std::string lieu; /*!< lieu de la réunion */
    std::string motif; /*!< motif de la réunion */
public:
    /*!
     * \brief Constructeur
     * \param n nom de la réunion
     * \param l lieu de la réunion
     * \param m motif de la réunion
     */
    Reunion(const std::string n, const std::string l, const std::string m):Evenement(n), lieu(l), motif(m) {}
    /*!
     * \brief getLieu
     * \return lieu de la réunion
     */
    std::string getLieu() const {
        return lieu;
    }
    /*!
     * \brief getMotif
     * \return motif de la réunion
     */
    std::string getMotif() const {
        return motif;
    }

};

#endif // REUNION_H
