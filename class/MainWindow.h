#ifndef CLASS_H
#define CLASS_H


#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLCDNumber>
#include <QSlider>
#include <QProgressBar>
#include <QMessageBox>
#include <QInputDialog>
#include <QDir>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QMessageLogger>
#include <QDateEdit>


class Main_Window : public QWidget
{
  Q_OBJECT

private:

    QGridLayout *_grid;
    QIcon *_Main_Window_icon;

    QGroupBox *_definition_groupbox;
    QVBoxLayout *_definition_layout;
    QLineEdit *_definition_name;
    QLineEdit *_definition_mother_class;
    QFormLayout *_definition_form_layout;


    QGroupBox *_options_groupbox;
    QVBoxLayout *_options_layout;
    QCheckBox *_options_protect_header;
    QCheckBox *_options_default_consturctor;
    QCheckBox *_options_default_destructor;


    QGroupBox *_comments_groupbox;
    QVBoxLayout *_comments_layout;
    QLineEdit *_comments_author;
    QDateEdit *_comments_creation_date;


    QTextEdit *_comments_class_role;
    QFormLayout *_comments_form_layout;

    QDialogButtonBox *_button_box;

protected:


public slots:
    void code_generater();

public:

    Main_Window();
};

#endif // CLASS_H
