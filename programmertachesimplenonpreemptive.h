#ifndef PROGRAMMERTACHESIMPLENONPREEMPTIVE_H
#define PROGRAMMERTACHESIMPLENONPREEMPTIVE_H

# include <QWidget>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QDateEdit>
# include <QTimeEdit>
# include <QFormLayout>
# include <QPushButton>
# include <projet.h>

class ProgrammerTacheSimpleNonPreemptive : public QWidget
{
    Q_OBJECT
protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    Projet& nomProjet;
    std::string * chemin;
    unsigned int* tailleChemin;
    std::string titreTache;
    QVBoxLayout* vBox;
    QHBoxLayout* hBox;
    QDateEdit* dateProgrammation;
    QTimeEdit* horaireProgrammation;
    QFormLayout* formlayout;
    QPushButton* annuler;  /*!< bouton annuler */
    QPushButton* sauver;  /*!< bouton sauver */
public:
    explicit ProgrammerTacheSimpleNonPreemptive(Projet& projet, std::string * chaine, unsigned int* taille, const std::string& titreT, QWidget *parent = 0);
signals:

public slots:
    void retourFenetrePrincipaleAnnuler();
    void retourFenetrePrincipaleSauver();
};

#endif // PROGRAMMERTACHESIMPLENONPREEMPTIVE_H
