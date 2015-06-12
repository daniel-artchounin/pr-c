#ifndef PROGRAMMATIONMANAGEREXCEPTION
#define PROGRAMMATIONMANAGEREXCEPTION

/*! \class ProgrammationManagerException
 *
 * Permet de générer des exception pour les ProgrammationManagers
 * Hérite de la classe Logic_error
 */
class ProgrammationManagerException : public std::logic_error {
public:
    /*!
     * \brief Constructeur
     *
     * Crée une exception avec une information sur celle-ci.
     *
     * \param m information sur l'exception
     */
    ProgrammationManagerException(const std::string& m):logic_error(m) {}
};

#endif // PROGRAMMATIONMANAGEREXCEPTION
