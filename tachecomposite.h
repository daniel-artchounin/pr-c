#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H
# include "tache.h"
# include "tachecompositeexception.h"
# include "tachesimplenonpreemptive.h"
# include "tachesimplepreemptive.h"
class TacheComposite : public Tache
{
    Tache** ssTaches;
    unsigned int nbSsTaches;
    unsigned int nbSsTachesMax;
    void addItem(Tache* t);
public:
    TacheComposite(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
          const Horaire& heureEcheance,const std::string & titre);
    Tache** getSsTaches() const;
    int getnbSsTaches();
    int getnbSsTachesMax();
    Tache* trouverSsTache(const std::string& nomTache);
    int trouverIndiceSsTache(const std::string& nomTache);
    Tache& ajouterSsTache(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
                        const Horaire& heureEcheance,const std::string & titre,const Duree & dur, bool preemptive);
    Tache& getSsTache(const std::string& titre);
    const Tache& getSsTache(const std::string& titre)const;
    void supprimerSsTache(const std::string& titre);
    ~TacheComposite();
};

#endif // TACHECOMPOSITE_H
