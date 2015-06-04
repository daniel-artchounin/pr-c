#ifndef PROGRAMMEREVENEMENT
#define PROGRAMMEREVENEMENT

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ProgrammerEvenement: public QWidget
{
    Q_OBJECT
protected :
    QFormLayout* formlayout;
    QLineEdit* nom; /*!< nom de l'évènement */
    QLineEdit* motif; /*!< motif de l'évènement */
    QLineEdit* lieu; /*!< lieu de l'évènement */
    QDateEdit* dateDebut;/*!< date de début */
    QTimeEdit* horaireDebut; /*!< horaire de début */
    QSpinBox* dureeHeure; /*!< duree heure*/
    QSpinBox* dureeMinute; /*!< duree heure*/
    QHBoxLayout* duree;
    QPushButton* valider;  /*!< bouton valider */
    QPushButton* annuler;  /*!< bouton annuler */
    QHBoxLayout* hBox;
    QVBoxLayout* vBox;

public:
    explicit ProgrammerEvenement(QWidget *parent = 0);

signals:

public slots:
    void closeEvent(QCloseEvent *event);
    virtual void programmer()=0;
    void quitter();
};

#endif // PROGRAMMEREVENEMENT

