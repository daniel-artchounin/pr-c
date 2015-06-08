#include "informationsprojet.h"
# include "informationselement.h"

InformationsProjet::InformationsProjet(const Projet& projet, QWidget *parent):
    InformationsElement(projet, parent)
{
    vBox->addLayout(formlayout);
    vBox->addLayout(hBoxOK);
}
