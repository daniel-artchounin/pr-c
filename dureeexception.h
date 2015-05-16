#ifndef DUREEEXCEPTION
#define DUREEEXCEPTION
#include <stdexcept>

/*!
 * \class DureeException
 * Permet de générer des exception pour les dates
 * Hérite de la classe Exception
 */
class DureeException : public std::logic_error{
public:
    /*!
     * \brief Constructeur
     * \param m information sur l'exception
     */
    DureeException(const std::string& m):logic_error(m) {}
};

#endif // DUREEEXCEPTION

