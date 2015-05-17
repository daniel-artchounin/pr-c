#ifndef TACHESIMPLENONPREEMPTIVE_H
#define TACHESIMPLENONPREEMPTIVE_H
# include "tachesimple.h"

class TacheSimpleNonPreemptive : public TacheSimple
{
public:
    TacheSimpleNonPreemptive(const Date& dateD, const Horaire& heureD, const Date& dateEcheance,
                             const Horaire& heureEcheance,const std::string & titre,const Duree & dur);
    // dureeValide()
};

#endif // TACHESIMPLENONPREEMPTIVE_H
