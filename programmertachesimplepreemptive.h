#ifndef PROGRAMMERTACHESIMPLEPREEMPTIVE_H
#define PROGRAMMERTACHESIMPLEPREEMPTIVE_H

# include <QWidget>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QDateEdit>
# include <QTimeEdit>
# include <QSpinBox>
# include <QFormLayout>
# include <QPushButton>
# include "projet.h"

class ProgrammerTacheSimplePreemptive : public QWidget
{
    Q_OBJECT
private :
    Projet& nomProjet;
    std::string * chemin;
    unsigned int* tailleChemin;
    QVBoxLayout* vBox;
    QHBoxLayout* hBox;
    QDateEdit* dateProgrammation;
    QTimeEdit* horaireProgrammation;
    QSpinBox * pourcentage;
    QFormLayout* formlayout;
    QPushButton* annuler;  /*!< bouton annuler */
    QPushButton* sauver;  /*!< bouton sauver */
public:
    explicit ProgrammerTacheSimplePreemptive(Projet& projet, std::string * chaine, unsigned int* taille, QWidget *parent = 0);

signals:

public slots:
    void retourFenetrePrincipale();
    void closeEvent(QCloseEvent *event);
};

#endif // PROGRAMMERTACHESIMPLEPREEMPTIVE_H
