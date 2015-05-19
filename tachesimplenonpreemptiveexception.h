#ifndef TACHESIMPLENONPREEMPTIVEEXCEPTION_H
#define TACHESIMPLENONPREEMPTIVEEXCEPTION_H
#include <stdexcept>

/*!
 * \class TacheSimpleNonPreemptiveException
 * Permet de générer des exceptions pour les TacheSimpleNonPreemptive
 * Hérite de la classe Logic_error
 */
class TacheSimpleNonPreemptiveException : public std::logic_error {
public:
    /*!
     * \brief Constructeur
     * \param m information sur l'exception
     */
    TacheSimpleNonPreemptiveException(const std::string& m):logic_error(m) {}
};
#endif // TACHESIMPLENONPREEMPTIVEEXCEPTION_H
