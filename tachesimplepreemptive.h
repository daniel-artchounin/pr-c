#ifndef TACHESIMPLEPREEMPTIVE_H
#define TACHESIMPLEPREEMPTIVE_H
# include "tachesimple.h"
class TacheSimplePreemptive : public TacheSimple
{
    unsigned int pourcentageComplete;
public:
    TacheSimplePreemptive(const Date& dateD,
                          const Horaire& heureD,
                          const Date& dateEcheance,
                          const Horaire& heureEcheance,
                          const std::string & titre,
                          const Duree & dur);
    unsigned int getPourcentageComplete()const;
    void setPourcentageComplete(int prt);
};

#endif // TACHESIMPLEPREEMPTIVE_H
