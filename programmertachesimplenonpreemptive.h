#ifndef PROGRAMMERTACHESIMPLENONPREEMPTIVE_H
#define PROGRAMMERTACHESIMPLENONPREEMPTIVE_H

# include <QWidget>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QDateEdit>
# include <QTimeEdit>
# include <QFormLayout>
# include <QPushButton>

class ProgrammerTacheSimpleNonPreemptive : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout* vBox;
    QHBoxLayout* hBox;
    QDateEdit* dateProgrammation;
    QTimeEdit* horaireProgrammation;
    QFormLayout* formlayout;
    QPushButton* annuler;  /*!< bouton annuler */
    QPushButton* sauver;  /*!< bouton sauver */
public:
    explicit ProgrammerTacheSimpleNonPreemptive(QWidget *parent = 0);

signals:

public slots:
    void retourFenetrePrincipale();
    void closeEvent(QCloseEvent *event);
};

#endif // PROGRAMMERTACHESIMPLENONPREEMPTIVE_H
