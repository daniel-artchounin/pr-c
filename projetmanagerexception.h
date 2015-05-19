#ifndef PROJETMANAGEREXCEPTION
#define PROJETMANAGEREXCEPTION
#include <stdexcept>

/*!
 * \class ProjetManagerException
 * Permet de générer des exception pour les ProjetManagers
 * Hérite de la classe Logic_error
 */
class ProjetManagerException : public std::logic_error {
public:
    /*!
     * \brief Constructeur
     * \param m information sur l'exception
     */
    ProjetManagerException(const std::string& m):logic_error(m) {}
};

#endif // PROJETMANAGEREXCEPTION
