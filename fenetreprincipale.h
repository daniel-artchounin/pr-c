#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QtWidgets>
#include "zonecentrale.h"
# include <tools.h>

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT
private:
    ZoneCentrale* zoneCentrale;
    QMenu* menuGestion;
    QMenu* menuFenetre;
    QMenu* menuAide;
    QToolBar* barrreOutils;
    QAction* actionSave;
    QAction* actionLoad;
    QAction* actionCreerProjet;
    QAction* actionQuitter;
    bool dejaSauver;
public:
    explicit FenetrePrincipale(QWidget *parent = 0);

signals:

public slots:
    void chargerFichier();
    void sauverFichier();
};

#endif // FENETREPRINCIPALE_H
