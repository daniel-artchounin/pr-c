#ifndef HoraireEXCEPTION
#define HoraireEXCEPTION
#include <stdexcept>

/*! \class HoraireException
 * Permet de générer des exception pour les Horaires
 * Hérite de la classe Logic_error
 */
class HoraireException : public std::logic_error {
public:
    /*!
     * \brief Constructeur
     * \param m information sur l'exception
     */
    HoraireException(const std::string& m):logic_error(m) {}
};

#endif // HoraireEXCEPTION

