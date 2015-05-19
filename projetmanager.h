#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H
#include "projet.h"
#include <vector>
#include <string>

class ProjetManager {
private:
    Projet** projets;
    unsigned int nb;
    unsigned int nbMax;
    void addItem(Projet* p);
    Projet* trouverProjet(const std::string& titre) const;

    //design pattern singleton
    static ProjetManager * instance;

    ProjetManager(): projets(0), nb(0), nbMax(0){}
    ~ProjetManager();
    ProjetManager(const ProjetManager& pm);
    ProjetManager& operator=(const ProjetManager& pm);
public:
    Projet& ajouterProjet(const Date& dateDebut, const Horaire& horaireDebut, const Date& dateFin, const Horaire& horaireFin, const std::string& titre);
    Projet& getProjet(const std::string& titre);
    const Projet& getProjet(const std::string& titre) const;

    //design pattern singleton
    static ProjetManager& getInstance();
    static void libererInstance();

    //Iterator méthode STL
    class iterator {
        Projet ** current;
        iterator(Projet ** projet) : current(projet) {}
        friend class ProjetManager;
    public :
        iterator():current(0) {}
        bool operator!=(const iterator & i) const {
            return i.current != this->current;
        }
        iterator & operator++(int) {
            ++current;
            return *this;
        }
        Projet & operator*() const {
            return **current;
        }
    };
    iterator begin() {
        return iterator(projets);
    }
    iterator end() {
        return iterator(projets+nb);
    }

    //iterator const
    class const_iterator {
        Projet ** current;
        const_iterator(Projet ** projet) : current(projet) {}
        friend class ProjetManager;
    public :
        const_iterator():current(0) {}
        bool operator!=(const const_iterator & i) const {
            return i.current != this->current;
        }
        const_iterator & operator++(int) {
            ++current;
            return *this;
        }
        Projet & operator*() const {
            return **current;
        }
    };
    const_iterator begin() const {
        return const_iterator(projets);
    }
    const_iterator end() const {
        return const_iterator(projets+nb);
    }
};

#endif // PROJETMANAGER_H
