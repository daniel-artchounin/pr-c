#ifndef CREERTACHESIMPLENONPREEMPTIVE_H
#define CREERTACHESIMPLENONPREEMPTIVE_H

# include <QWidget>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QFormLayout>
# include <QLineEdit>
# include <QDateEdit>
# include <QPushButton>
# include <QSpinBox>
# include <QCloseEvent>
# include <QLabel>
# include <QMessageBox>
# include "fenetreprincipale.h"

class CreerTacheSimpleNonPreemptive : public QWidget
{
    Q_OBJECT
protected :
    virtual void closeEvent(QCloseEvent *event);
private :
    Projet& nomProjet;
    std::string * chemin;
    unsigned int* tailleChemin;
    QVBoxLayout* vBox;
    QHBoxLayout* hBox1;
    QHBoxLayout* hBox2;
    QFormLayout* formlayout;
    QLineEdit* titre; /*!< titre de l'élément */
    QDateEdit* dateDebut;/*!< date de début */
    QTimeEdit* horaireDebut; /*!< horaire de début */
    QDateEdit* dateFin; /*!< date de fin */
    QTimeEdit* horaireFin; /*!< horaire de fin */
    QLabel* labelH; /*!< label : heures */
    QSpinBox *heures; /*!< durée : nombre d'heures */
    QLabel* labelM;   /*!< label : minutes */
    QSpinBox *minutes; /*!< durée :  nombre de minutes */
    QPushButton* annuler;  /*!< bouton annuler */
    QPushButton* sauver;  /*!< bouton sauver */
public:
    explicit CreerTacheSimpleNonPreemptive(Projet& projet, std::string * chaine, unsigned int* taille, QWidget *parent = 0);

signals:

public slots:
    void retourFenetrePrincipaleAnnuler();
    void retourFenetrePrincipaleSauver();
};
#endif // CREERTACHESIMPLENONPREEMPTIVE_H
