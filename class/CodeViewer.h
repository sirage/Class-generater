#ifndef CODEVIEWER_H
#define CODEVIEWER_H


#include <MainWindow.h>
#include <QTextStream>

class Code_Viewer : public QDialog
{

    Q_OBJECT

private:
    QGridLayout *_main_grid;

    QIcon *_Code_Viewer_icon;

    QDialogButtonBox *_code_button_box;
    QPushButton *_save;
    QPushButton *_exit;

protected:

public slots:
    void code_exit_msgBox_function();
    void save_to_file();

public:
    //bool was_saved(bool &vlaue);
    void bool_check();
    QTextEdit *_code_display;
    Code_Viewer(QString &code , QWidget *parent);

    QMessageBox::StandardButton _code_exit_msgBox ( QWidget *parent, const QString &title, const QString &text,
                                               QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                              QMessageBox::StandardButton defaultButton = QMessageBox::NoButton );
};


#endif // CODEVIEWER_H
