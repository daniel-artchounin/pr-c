#ifndef ZONECENTRALE_H
#define ZONECENTRALE_H
#include <QTabWidget>
# include "fenetregestionprojet.h"
# include "fenetreedt.h"
#include <QWidget>

class FenetreGestionProjet;
class ZoneCentrale : public QWidget
{
    Q_OBJECT
private:
    // QTabWidget* onglets;
    FenetreEDT* fenetreEDT;
    FenetreGestionProjet* fenetreGestionProjet;
    QHBoxLayout* hBox;
public:
    explicit ZoneCentrale(QWidget *parent = 0);
    FenetreGestionProjet* getFenetreGestionProjet()const{
        return fenetreGestionProjet;
    }
    FenetreEDT* getFenetreEDT()const{
        return fenetreEDT;
    }

signals:

public slots:

};

#endif // ZONECENTRALE_H
