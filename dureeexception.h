#ifndef DUREEEXCEPTION
#define DUREEEXCEPTION
#include <stdexcept>

/*! \class DureeException
 *
 * Permet de générer des exception pour les durees
 * Hérite de la classe Logic_error
 */
class DureeException : public std::logic_error {
public:
    /*!
     * \brief Constructeur
     *
     * Crée une exception avec une information sur celle-ci.
     *
     * \param m information sur l'exception
     */
    DureeException(const std::string& m):logic_error(m) {}
};

#endif // DUREEEXCEPTION

