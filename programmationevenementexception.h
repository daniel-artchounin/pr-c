#ifndef PROGRAMMATIONEVENEMENTEXCEPTION
#define PROGRAMMATIONEVENEMENTEXCEPTION

/*! \class ProgrammationEvenementException
 * Permet de générer des exception pour les programmations d'évènements
 * Hérite de la classe Logic_error
 */
class ProgrammationEvenementException : public std::logic_error {
public:
    /*!
     * \brief Constructeur
     * \param m information sur l'exception
     */
    ProgrammationEvenementException(const std::string& m):logic_error(m) {}
};

#endif // PROGRAMMATIONEVENEMENTEXCEPTION

