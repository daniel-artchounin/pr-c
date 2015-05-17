#ifndef TACHESIMPLE_H
#define TACHESIMPLE_H
#include "duree.h"
#include "date.h"
#include "horaire.h"
#include "tache.h"
class TacheSimple : public Tache
{
    Duree duree;
    bool termine;
public:
    const Duree & getDuree()const;
    // getDateFin
    // getHeureFin
    bool isTermine()const;
    void setTermine(bool state);
    TacheSimple(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
                const Horaire& heureEcheance,const std::string & titre,const Duree & dur);
};

#endif // TACHESIMPLE_H
