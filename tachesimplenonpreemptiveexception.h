#ifndef TACHESIMPLENONPREEMPTIVEEXCEPTION_H
#define TACHESIMPLENONPREEMPTIVEEXCEPTION_H

/*! \class TacheSimpleNonPreemptiveException
 *
 * Permet de générer des exceptions pour les TacheSimpleNonPreemptive
 * Hérite de la classe Logic_error
 */
class TacheSimpleNonPreemptiveException : public std::logic_error {
public:
    /*!
     * \brief Constructeur
     *
     * Crée une exception avec une information sur celle-ci.
     *
     * \param m information sur l'exception
     */
    TacheSimpleNonPreemptiveException(const std::string& m):logic_error(m) {}
};
#endif // TACHESIMPLENONPREEMPTIVEEXCEPTION_H
