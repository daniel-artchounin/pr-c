#ifndef TOOLSEXCEPTION
#define TOOLSEXCEPTION
#include <stdexcept>

/*! \class ToolsException
 *
 * Permet de générer des exception pour les méthodes de Tools
 * Hérite de la classe Logic_error
 */
class ToolsException : public std::logic_error {
public:
    /*!
     * \brief Constructeur
     *
     * Crée une exception avec une information sur celle-ci.
     *
     * \param m information sur l'exception
     */
    ToolsException(const std::string& m):logic_error(m) {}
};

#endif // TOOLSEXCEPTION

