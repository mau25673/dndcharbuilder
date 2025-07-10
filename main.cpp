#include "mainwindow.h"
#include <QApplication>
#include <QApplication>
#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.setWindowTitle("D&D Character Builder");
    window.show();
    window.setWindowIcon(QIcon(":/icons/icons/dnd-icon.png"));
    return a.exec();

}
