#ifndef INFORMATIONSELEMENT_H
#define INFORMATIONSELEMENT_H
# include "element.h"
# include <QPushButton>
# include <QHBoxLayout>
# include <QLabel>
# include <QWidget>
# include <QFormLayout>

class InformationsElement : public QWidget
{
    Q_OBJECT
protected:
    QFormLayout* formlayout;
    QPushButton* ok;  /*!< bouton ok */
    QHBoxLayout* hBoxOK;
    QVBoxLayout* vBox; // pour harmoniser le tout
    QLabel *titre;
    QLabel *dateDebut;
    QLabel *horaireDebut;
    QLabel *dateEcheance;
    QLabel *heureEcheance;
    QLabel *duree;
    virtual void closeEvent(QCloseEvent *event);
public:
    explicit InformationsElement(const Element& element, QWidget *parent = 0);
signals:

public slots:
    void retourFenetrePrincipale();

};

#endif // INFORMATIONSELEMENT_H
