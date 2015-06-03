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

class ProgrammerTacheSimplePreemptive : public QWidget
{
    Q_OBJECT
private :
    QVBoxLayout* vBox;
    QHBoxLayout* hBox;
    QDateEdit* dateProgrammation;
    QTimeEdit* horaireProgrammation;
    QSpinBox * pourcentage;
    QFormLayout* formlayout;
    QPushButton* annuler;  /*!< bouton annuler */
    QPushButton* sauver;  /*!< bouton sauver */
public:
    explicit ProgrammerTacheSimplePreemptive(QWidget *parent = 0);

signals:

public slots:
    void retourFenetrePrincipale();
    void closeEvent(QCloseEvent *event);
};

#endif // PROGRAMMERTACHESIMPLEPREEMPTIVE_H
