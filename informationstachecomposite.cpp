#include "informationstachecomposite.h"

InformationsTacheComposite::InformationsTacheComposite(const TacheComposite& tacheComposite, QWidget *parent):
    InformationsTache(tacheComposite, parent)
{
    vBox->addLayout(formlayout);
    if(vBoxPrecedence!=0){
        vBox->addLayout(vBoxPrecedence);
    }
    vBox->addLayout(hBoxOK);
}
