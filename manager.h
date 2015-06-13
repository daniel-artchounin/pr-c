#ifndef MANAGER_H
#define MANAGER_H
#include <map>
#include <string>
#include <QXmlStreamWriter>
# include <iostream>
/*! \class Manager
 * \brief Patron de classe permettant de manipuler une map d'item.
 */
template <class T> class Manager {

    friend class TacheSimplePreemptive;
    friend class TacheSimpleNonPreemptive;
    friend class FenetreGestionProjet;

protected:

    typedef std::map<std::string, T*> Map;
    Map items; /*!< map d'item */

    /*!
     * \brief addItem
     * Ajout un objet à la map.
     * \param key clé de l'item à ajouter
     * \param item item à ajouter
     * \return true si l'item à été ajouté, false sinon
     */
    bool addItem(std::string key, T* item) {
        std::pair<iterator,bool> retour = items.insert(std::pair<std::string, T*>(key, item));
        return retour.second;
    }

    /*!
     * \brief eraseItem
     * Supprime un objet de la map.
     * \param key identifiant de l'objet dans la map
     * \return la taille de l'élément supprimé, 0 si rien n'a été supprimé
     */
    int eraseItem(const std::string& key){
        T* element = getItem(key);
        if(element!=0){
            delete element;
        }
        return int(items.erase(key));
    }

    /*!
     * \brief getIte m
     * \param key clé de l'item à trouver
     * \return item si trouvé, 0 sinon
     */
    T* getItem(std::string key) const {
        const_iterator result = items.find(key);
        if(result == end()) {
            return 0;
        }
        return result->second;
    }

public:
    /*!
     * \brief Constructeur
     * Initialise la map.
     */
    Manager():items(){}

    /*!
     * \brief Destructeur
     * Destructeur virtuel.
     */
    virtual ~Manager() {
        for(iterator it=items.begin(); it!=items.end(); ++it) {
            delete it->second;
        }
        items.clear();
    }

    /*!
     * \brief Constructeur par recopie
     * \param m Manager à recopier
     */
    Manager(const Manager& m): items() {
        for(iterator it=m.items.begin(); it!=m.items.end(); ++it) {
            items.insert(std::pair<std::string, T*>(it->first, it->second));
        }
    }

    /*!
     * \brief Opérateur d'affectation
     * \param m Manager
     * \return Manager
     */
    Manager& operator=(const Manager& m) {
        if (this==&m) return *this;
        this->~Manager();
        for(iterator it=m.items.begin(); it!=m.items.end(); ++it) items.insert(std::pair<std::string, T*>(it->first, it->second));
        return *this;
    }

    typedef typename Map::iterator iterator;
    typedef typename Map::const_iterator const_iterator;

    /*!
     * \brief begin
     * \return iterator sur le début de la map
     */
    iterator begin() { return items.begin(); }

    /*!
     * \brief end
     * \return iterator sur la fin de la map
     */
    iterator end() { return items.end(); }

    /*!
     * \brief begin
     * Sera utilisé si on utilise une référence const ou * un pointeur const vers un objet de type Element ou d'un type descendant d'Element.
     * \return const_iterator sur le début de la map
     */
    const_iterator begin() const { return const_cast<Manager*>(this)->begin(); }

    /*!
     * \brief end
     * Sera utilisé si on utilise une référence const ou un pointeur const vers un objet de type Element ou d'un type descendant d'Element.
     * \return const_iterator sur la fin de la map
     */
    const_iterator end() const { return const_cast<Manager*>(this)->end(); }

    /*!
     * \brief exportTo
     * Permet d'exporter les données dans un fichier XML via le streamwriter.
     * \param stream
     */
    virtual void exportTo(QXmlStreamWriter& stream) {
        for(iterator it=begin(); it!=end(); ++it){
            (*it->second).exportTo(stream);
        }
    }
};

#endif // MANAGER_H
