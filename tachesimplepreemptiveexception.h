#ifndef TACHESIMPLEPREEMPTIVEEXCEPTION_H
#define TACHESIMPLEPREEMPTIVEEXCEPTION_H
#include <stdexcept>

/*!
 * \class TacheSimplePreemptiveException
 * Permet de générer des exceptions pour les TacheSimplePreemptive
 * Hérite de la classe Logic_error
 */
class TacheSimplePreemptiveException : public std::logic_error {
public:
    /*!
     * \brief Constructeur
     * \param m information sur l'exception
     */
    TacheSimplePreemptiveException(const std::string& m):logic_error(m) {}
};
#endif // TACHESIMPLEPREEMPTIVEEXCEPTION_H
