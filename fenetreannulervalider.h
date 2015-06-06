#ifndef FENETREANNULERVALIDER_H
#define FENETREANNULERVALIDER_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class FenetreAnnulerValider : public QWidget
{
    Q_OBJECT
protected :
    QPushButton* valider;  /*!< bouton valider */
    QPushButton* annuler;  /*!< bouton annuler */
    QHBoxLayout* hBoxAnnulerValider;
    QVBoxLayout* vBox; // pour harmoniser le tout
    virtual void closeEvent(QCloseEvent *event);
public:
    explicit FenetreAnnulerValider(QWidget *parent = 0);
signals:

public slots:
    void retourFenetrePrincipaleAnnuler();
    virtual void retourFenetrePrincipaleValider()=0;
};

#endif // FENETREANNULERVALIDER_H
