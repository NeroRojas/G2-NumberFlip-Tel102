#include "mainwindow.h"
#include "intro_dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IntroDialog intro;
    if (intro.exec() == QDialog::Accepted) {
        MainWindow w;
        w.show();
        return a.exec();
    }

    return 0;
}
