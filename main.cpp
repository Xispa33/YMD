#include "fenetreprincipale.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //qDebug() << "hello";
    //return app.exec();
    FenetrePrincipale appli;
    appli.show();

    return app.exec();

}
