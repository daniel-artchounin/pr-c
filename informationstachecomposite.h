#ifndef INFORMATIONSTACHECOMPOSITE_H
#define INFORMATIONSTACHECOMPOSITE_H
# include "tachecomposite.h"
# include "informationstache.h"

class InformationsTacheComposite : public InformationsTache
{
public:
    InformationsTacheComposite(const TacheComposite& tacheComposite, QWidget *parent = 0);
};

#endif // INFORMATIONSTACHECOMPOSITE_H
