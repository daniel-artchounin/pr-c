#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <string>

/*! \class Evenement
   * \brief Classe possédant un nom. Correspond à un évènement traditionnel.
   */
class Evenement
{
protected:
    std::string nom; /*!< nom de l'évènement */
public:
    /*!
     * \brief Constructeur
     * \param n nom de l'évènement
     */
    Evenement(const std::string n):nom(n){}

    /*!
     * \brief Desctructeur
     * Destructeur virtual pure.
     */
    virtual ~Evenement()=0;

    /*!
     * \brief getNom
     * \return nom de l'évènement
     */
    std::string getNom() const{
        return nom;
    }
};

#endif // EVENEMENT_H
