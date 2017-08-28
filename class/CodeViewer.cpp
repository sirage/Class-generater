#include "CodeViewer.h"



const QString Code_Viewer_icon=("debug/code_icon.png");

Code_Viewer::Code_Viewer(QString &code, QWidget *parent = 0) : QDialog(parent)
{
    _main_grid = new QGridLayout;
    setFixedSize(600,650);

    _Code_Viewer_icon = new QIcon;
    setWindowIcon(QIcon(Code_Viewer_icon));

    //============== ESSENTIALS DONT TOUCH =========================
    _code_display = new QTextEdit(this);
    _code_display->setPlainText(code);
    _code_display->setReadOnly(true);
    //==============================================================



    _code_button_box = new QDialogButtonBox(QDialogButtonBox::Ok|
                                            QDialogButtonBox::Cancel);

    _code_button_box->button(QDialogButtonBox::Ok)->setText("Save");
    _code_button_box->button(QDialogButtonBox::Ok)->setToolTip("Save code to a text file (txt format)");
    _code_button_box->button(QDialogButtonBox::Cancel)->setText("Exit");

    QObject::connect(_code_button_box,SIGNAL(accepted()),this,SLOT(save_to_file()));
    QObject::connect(_code_button_box,SIGNAL(rejected()),this,SLOT(code_exit_msgBox_function()));


    _main_grid->addWidget(_code_display,1,0);
    _main_grid->addWidget(_code_button_box,5,0);
    setLayout(_main_grid);


}

//=====================
bool was_saved = false; //bool signal that the code was not saved => fasle
//=====================

void Code_Viewer::save_to_file()
{
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     "Save code","class","cpp file (*.cpp);;All Files (*)");
    if(file_name.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(file_name);
        if(!file.open(QIODevice::WriteOnly))
        {

            QMessageBox::information(this,"Unable tp open file",file.errorString());
            return;
        }
        QTextStream stream (&file);
        stream << _code_display->toPlainText();
    }

    was_saved = true; //change the glabal value into true to signal that the code was saved
}





void Code_Viewer::code_exit_msgBox_function()
{

    if(was_saved == true) //if the code was saved you can simply quit the code
    {
        qApp -> quit();
    }

    if(was_saved == false)
    {
        // http://doc.qt.io/qt-4.8/qmessagebox.html#standardButtons-prop

        QMessageBox msgBox;
        msgBox.setText("Exit with out saving");
        QPushButton *yesButton = msgBox.addButton("Yes",QMessageBox::YesRole);
        QPushButton *cancelButton = msgBox.addButton("Cancel",QMessageBox::NoRole);
        QPushButton *saveButton = msgBox.addButton("Save" , QMessageBox::YesRole);

        msgBox.exec();

        if(msgBox.clickedButton() == yesButton)
        {
            qApp->quit();
        }


        if(msgBox.clickedButton() == saveButton)
        {
            save_to_file();
        }

        if(msgBox.clickedButton() == cancelButton)
        {

        }
    }
}

















