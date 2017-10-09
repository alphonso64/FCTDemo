#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QFile file("C:\\Program Files\\LedAoi\\key.lc");
    if(file.exists())
    {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }else{
        return -1;
    }

}
