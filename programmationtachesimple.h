#ifndef PROGRAMMATIONTACHESIMPLE_H
#define PROGRAMMATIONTACHESIMPLE_H
#include "tachesimple.h"
# include "programmation.h"

class ProgrammationTacheSimple : public Programmation{
    protected :

        bool checkPrecedentsTerminees(){
            return true;
        }
        bool checkDateDebut(){
            return true;

        }
        bool checkDateFin(){
            return true;

        }
    public:
        ProgrammationTacheSimple(const Date&  dateDebut, const Horaire & horaireDebut):Programmation(dateDebut, horaireDebut){
        }
        virtual ~ProgrammationTacheSimple(){}
};

#endif // PROGRAMMATIONTACHESIMPLE_H




