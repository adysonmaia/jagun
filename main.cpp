#include <QApplication>
#include <iostream>
#include "mainWindow.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    MainWindow *jagun = new MainWindow;
    
    jagun->setWindowTitle(QObject::tr("Jagun"));
    jagun->resize(800, 600);
    jagun->show();
    return app.exec();
}

