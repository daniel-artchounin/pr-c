#ifndef TACHE_H
#define TACHE_H
#include "element.h"
#include <map>
#include "tacheexception.h"

/*! \class Tache
 * \brief Classe permettant de manipuler des taches
 * Cette classe est abstraite
 */
class Tache : public Element {

protected:

    typedef std::map<std::string, Tache*> TPMap;
    TPMap tachesPrecedentes; /*!< map de taches */
    TPMap tachesSuivantes; /*!< map de taches */

    /*!
     * \brief trouverTachePrecedente
     * permet de trouver la tâche précédente envoyée en paramètre
     * parmi les contraintes de precedence de la tâche actuelle
     * \param titre titre de la tache potentiellement précédente
     * \return retourne un pointeur vers la tâche précédente si elle l'est vraiment
     * ou 0 sinon
     */
    Tache* trouverTachePrecedente(const std::string& titre) const;

    /*!
     * \brief trouverTacheSuivante
     * permet de trouver la tâche suivante envoyée en paramètre
     * parmi les contraintes de "suivance" de la tâche actuelle
     * \param titre titre de la tache potentiellement suivante
     * \return retourne un pointeur vers la tâche suivante si elle l'est vraiment
     * ou 0 sinon
     */
    Tache* trouverTacheSuivante(const std::string & titre)const;

public:

    /*!
     * \brief Constructeur
     * \param dateD date de disponiblité
     * \param heureD heure de disponiblité
     * \param dateEcheance date d'échéance
     * \param heureEcheance heure d'échéance
     * \param titre titre de la tache
     */
    Tache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
          const Horaire& heureEcheance,const std::string & titre,const Duree& dur=0);

    /*!
     * \brief isTachePrecedente
     * permet de savoir si une tâche envoyée en paramètre précède la tâche courante
     * \param titre titre d'une potentielle tache précédente
     * \return retourne un booléen (en fonction du statut de la tache par rapport à la tâche actuelle)
     */
    bool isTachePrecedente(const std::string& titre) const;

    /*!
     * \brief isTacheSuivante
     * permet de savoir si une tâche envoyée en paramètre succède la tâche courante
     * \param titre titre d'une potentielle tache suivante
     * \return retourne un booléen (en fonction du statut de la tache par rapport à la tâche actuelle)
     */
    bool isTacheSuivante(const std::string& titre) const;

    /*!
     * \brief getTachePrecedente
     * permet de trouver une tâche précédente de la tâche courante
     * déclenche une exception si la tâche n'est pas trouvée
     * \param titre nom de la tâche
     * \return retourne une référence sur la tâche précédente
     */
    Tache& getTachePrecedente(const std::string& titre);

    /*!
     * \brief getTachePrecedente
     * permet de trouver une tâche suivante de la tâche courante
     * déclenche une exception si la tâche n'est pas trouvée
     * \param titre nom de la tâche
     * \return retourne une référence sur la tâche suivante
     */
    Tache& getTacheSuivante(const std::string& titre);

    /*!
     * \brief getTachePrecedente accesseur méthode const (elle sera utilisé par les références
     * const ou les pointeurs const)
     * permet de trouver une tâche précédente de la tâche courante
     * déclenche une exception si la tâche n'est pas trouvée
     * \param titre nom de la tâche
     * \return retourne une référence sur la tâche précédente
     */
    const Tache& getTachePrecedente(const std::string& titre)const{
        return const_cast<Tache*>(this)->getTachePrecedente(titre);
    }

    /*!
     * \brief getTacheSuivante accesseur méthode const (elle sera utilisé par les références
     * const ou les pointeurs const)
     * permet de trouver une tâche suivante de la tâche courante
     * déclenche une exception si la tâche n'est pas trouvée
     * \param titre nom de la tâche
     * \return retourne une référence sur la tâche suivante
     */
    const Tache& getTacheSuivante(const std::string& titre)const{
        return const_cast<Tache*>(this)->getTacheSuivante(titre);
    }

    /*!
     * \brief ajouterTachePrecedente
     * ajoute une tâche précédente à la tâche courante
     * \param cheminementPrecedent chemin de la tache précédente
     * \param cheminementSuivant chemin de la tache suivante
     */
    void ajouterTachePrecedente(Tache & tachePrecedente, const std::string& cheminementPrecedent, const std::string& cheminementSuivant);

    /*!
     * \brief ajouterTacheSuivante
     * ajoute une tâche suivante à la tâche courante
     * \param cheminementPrecedent chemin de la tache précédente
     * \param cheminementSuivant chemin de la tache suivante
     */
    void ajouterTacheSuivante(Tache & tacheSuivante, const std::string& cheminementPrecedent, const std::string& cheminementSuivant);


    /*!
     * \brief supprimerTachesPrecedente
     * supprime une contrainte de précedence
     * \param tachePrecedente référence sur une tache à supprimer
     */
    void supprimerTachePrecedente(const std::string& tachePrecedente);

    /*!
     * \brief supprimerTacheSuivante
     * supprime une contrainte de "suivance"
     * \param tacheSuivante référence sur une tache à supprimer
     */
    void supprimerTacheSuivante(const std::string & tacheSuivante);

    typedef typename TPMap::iterator tp_iterator;
    typedef typename TPMap::const_iterator tp_const_iterator;
    typedef typename TPMap::iterator ts_iterator;
    typedef typename TPMap::const_iterator ts_const_iterator;

    /*!
     * \brief tPBegin
     * \return iterator sur le début de la map
     */
    tp_iterator tPBegin() { return tachesPrecedentes.begin(); }

    /*!
     * \brief tPEnd
     * \return iterator sur la fin de la map
     */
    tp_iterator tPEnd() { return tachesPrecedentes.end(); }

    /*!
     * \brief tPSize
     * \return taille de la map des taches précédentes
     */
    int tPSize()const{
        return int(tachesPrecedentes.size());
    }

    /*!
     * \brief tPBegin
     * \return const_iterator sur le début de la map
     */
    tp_const_iterator tPBegin() const{ return const_cast<Tache *>(this)->tPBegin(); }

    /*!
     * \brief tPEnd
     * \return const_iterator sur la fin de la map
     */
    tp_const_iterator tPEnd() const{ return const_cast<Tache *>(this)->tPEnd(); }

    /*!
     * \brief tPBegin
     * \return iterator sur le début de la map
     */
    ts_iterator tSBegin() { return tachesSuivantes.begin(); }

    /*!
     * \brief tPEnd
     * \return iterator sur la fin de la map
     */
    ts_iterator tSEnd() { return tachesSuivantes.end(); }

    /*!
     * \brief tPBegin
     * \return const_iterator sur le début de la map
     */
    ts_const_iterator tSBegin() const{ return const_cast<Tache *>(this)->tSBegin(); }

    /*!
     * \brief tPEnd
     * \return const_iterator sur la fin de la map
     */
    ts_const_iterator tSEnd() const{ return const_cast<Tache *>(this)->tSEnd(); }

    /*!
     * \brief tSSize
     * \return taille de la map des taches suivantes
     */
    int tSSize()const{
        return int(tachesSuivantes.size());
    }

    /*!
     * \brief checkProgrammationCoherente
     * permet de savoir si les tâches précédent ma tâche ont
     * toutes été programmés et si fin de la programmation est
     * antérieure à la programmation de ma tâche
     * \param dateProg date de programmation
     * \param horaireProg horaire de programmation
     * \param tacheActuelle pointeur sur la tâche actuelle dans la boucle récursive
     * (ne doit pas être utilisé par le client)
     * \return vrai si la programmation est correcte ou faux sinon
     */
    bool checkProgrammationCoherente(const Date& dateProg, const Horaire& horaireProg, const Tache* tacheActuelle=0)const;

    /*!
     * \brief exportTo
     *
     * Permet d'exporter les données dans un fichier XML via le streamwriter, notamment les contraintes de précédences
     *
     * \param stream
     */
    virtual void exportTo(QXmlStreamWriter& stream);

    /*!
     * \brief exportProgrammations
     *
     * Permet d'exporter les programmations de la tache
     *
     * \param stream
     */
    virtual void exportProgrammations(QXmlStreamWriter& stream)=0;

    /*!
     * \brief ~Tache destructeur
     */
    virtual ~Tache();
};

#endif // TACHE_H
