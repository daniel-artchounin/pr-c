#ifndef DATEEXCEPTION
#define DATEEXCEPTION

/*! \class DateException
 *
 * Permet de générer des exception pour les dates
 * Hérite de la classe Logic_error
 */
class DateException : public std::logic_error {
public:
    /*!
     * \brief Constructeur
     *
     * Crée une exception avec une information sur celle-ci.
     *
     * \param m information sur l'exception
     */
    DateException(const std::string& m):logic_error(m) {}
};

#endif // DATEEXCEPTION
