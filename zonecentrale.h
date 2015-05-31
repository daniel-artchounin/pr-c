#ifndef ZONECENTRALE_H
#define ZONECENTRALE_H
#include <QTabWidget>
# include "fenetregestionprojet.h"
# include "fenetreedt.h"
#include <QWidget>

class ZoneCentrale : public QWidget
{
    Q_OBJECT
private:
    QTabWidget* onglets;
    FenetreEDT* fenetreEDT;
    FenetreGestionProjet* fenetreGestionProjet;
public:
    explicit ZoneCentrale(QWidget *parent = 0);

signals:

public slots:

};

#endif // ZONECENTRALE_H
