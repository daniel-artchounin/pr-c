#ifndef CREERTACHESIMPLEPREEMPTIVE_H
#define CREERTACHESIMPLEPREEMPTIVE_H

# include <QWidget>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QFormLayout>
# include <QLineEdit>
# include <QDateEdit>
# include <QPushButton>
# include <QSpinBox>
# include <QLabel>
# include <QMessageBox>
# include "fenetreprincipale.h"
# include "creertache.h"

class CreerTacheSimplePreemptive : public CreerTache
{
    Q_OBJECT
protected :
    QHBoxLayout* hBox1;
    QLabel* labelH; /*!< label : heures */
    QSpinBox *heures; /*!< durée : nombre d'heures */
    QLabel* labelM;   /*!< label : minutes */
    QSpinBox *minutes; /*!< durée :  nombre de minutes */
public:
    explicit CreerTacheSimplePreemptive(Projet& projet, std::string * chaine, unsigned int* taille, QWidget *parent = 0);

signals:

public slots:
    void retourFenetrePrincipaleValider();
};
#endif // CREERTACHESIMPLEPREEMPTIVE_H
