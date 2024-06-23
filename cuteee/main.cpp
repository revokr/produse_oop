#include "cuteee.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    
    QApplication a(argc, argv);
    repo p{ "C:\\Users\\rafael\\source\\repos\\cuteee\\cuteee\\produse.txt" };
    vali v;
    service srv{ p, v };
    GUI app{ srv };
    app.show();
    return a.exec();
}
