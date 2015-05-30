#ifndef PROGRAMMATIONMANAGEREXCEPTION
#define PROGRAMMATIONMANAGEREXCEPTION

#include <stdexcept>

/*! \class ProgrammationManagerException
 * Permet de générer des exception pour les ProgrammationManagers
 * Hérite de la classe Logic_error
 */
class ProgrammationManagerException : public std::logic_error {
public:
    /*!
     * \brief Constructeur
     * \param m information sur l'exception
     */
    ProgrammationManagerException(const std::string& m):logic_error(m) {}
};

#endif // PROGRAMMATIONMANAGEREXCEPTION
