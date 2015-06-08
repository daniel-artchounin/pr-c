#ifndef INFORMATIONSPROJET_H
#define INFORMATIONSPROJET_H
# include "projet.h"
# include "informationselement.h"

class InformationsProjet : public InformationsElement
{
public:
    InformationsProjet(const Projet& projet, QWidget *parent = 0);
};

#endif // INFORMATIONSPROJET_H
