# include <QApplication>
# include <QPushButton>
# include <projetmanager.h>
# include <programmationmanager.h>
# include <string>
# include <QtWidgets>
# include <fenetreprincipale.h>
# include "tools.h"
using namespace std;

int main(int argc, char * argv[]){
    QApplication myApp(argc, argv);
    FenetrePrincipale fenetrePrincipale;
    fenetrePrincipale.showMaximized();
    return myApp.exec();
}
