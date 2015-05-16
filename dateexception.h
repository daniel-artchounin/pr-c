#ifndef DATEEXCEPTION
#define DATEEXCEPTION
#include "stdexcept"

/*!
 * \class DateException
 * Permet de générer des exception pour les dates
 * Hérite de la classe Exception
 */
class DateException : public std::logic_error{
public:
    /*!
     * \brief Constructeur
     * \param m information sur l'exception
     */
    DateException(const std::string& m):logic_error(m) {}
};

#endif // DATEEXCEPTION
