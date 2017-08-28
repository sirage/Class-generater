#include <QApplication>
#include <QPushButton>
#include <QFont>
#include <QWidget>
#include <QIcon>
#include <QInputDialog>
#include <QBoxLayout>

#include <MainWindow.h>

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    Main_Window main_window;
    main_window.show();

    app.exec();
}
