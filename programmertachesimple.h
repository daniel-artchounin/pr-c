#ifndef PROGRAMMERTACHESIMPLE_H
#define PROGRAMMERTACHESIMPLE_H
# include "fenetreannulervalider.h"
# include "projet.h"
# include <QDateEdit>
# include <QFormLayout>
# include <QLabel>

class ProgrammerTacheSimple : public FenetreAnnulerValider
{
protected:
    Projet& nomProjet;
    std::string * chemin;
    unsigned int* tailleChemin;
    std::string titreTache;
    QDateEdit* dateProgrammation;
    QTimeEdit* horaireProgrammation;
    QLabel *titre;
    QLabel *dateDebut;
    QLabel *horaireDebut;
    QLabel *dateEcheance;
    QLabel *heureEcheance;
    QLabel *duree;
    QFormLayout* formlayout;
    virtual void closeEvent(QCloseEvent *event);
public:
    ProgrammerTacheSimple(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent = 0);
};

#endif // PROGRAMMERTACHESIMPLE_H
