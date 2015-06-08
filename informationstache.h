#ifndef INFORMATIONSTACHE_H
#define INFORMATIONSTACHE_H
# include "informationselement.h"
# include "tache.h"
# include <QTableWidget>
# include <QTableWidgetItem>


class InformationsTache : public InformationsElement
{
public:
    InformationsTache(const Tache& tache, QWidget *parent = 0);
    QTableWidget* precendentTableWidget;
    QTableWidget* suivantTableWidget;
    QVBoxLayout* vBoxPrecedence;
};

#endif // INFORMATIONSTACHE_H
