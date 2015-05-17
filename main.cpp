# include <QApplication>
# include <QPushButton>

int main(int argc, char * argv[]){
    QApplication myApp(argc, argv);
    QPushButton bouton("Bonjour");
    bouton.show();
    return myApp.exec();
}
