#include "MainWindow.h"
#include "CodeViewer.h"

const QString Main_Window_icon = ("debug/main_icon");

Main_Window::Main_Window() : QWidget()
{
    setFixedSize(600,650);
    _grid = new QGridLayout; //setted layout are at the end of the constructor

    _Main_Window_icon = new QIcon;
    setWindowIcon(QIcon(Main_Window_icon));

    //============================  DEFINITION  ================================

    _definition_groupbox = new QGroupBox("Definition of the class", this);
    _definition_layout = new QVBoxLayout;

    _definition_name = new QLineEdit;//("Name : ",this);
    _definition_mother_class = new QLineEdit;//("Mother class : ",this);

    _definition_form_layout = new QFormLayout;
    _definition_form_layout->addRow("&Name",_definition_name);
    _definition_form_layout->addRow("&Parent class" , _definition_mother_class);

    _definition_layout->addLayout(_definition_form_layout);

    _definition_groupbox->setLayout(_definition_layout);

    //============================  OPTIONS  ================================

    _options_groupbox = new QGroupBox("Options", this);
    _options_layout = new QVBoxLayout;

    _options_protect_header =
            new QCheckBox("Protect the header from multiple inclusions", this);
    _options_default_consturctor =
            new QCheckBox("Generate a default constructor" ,this);
    _options_default_destructor=
            new QCheckBox("Generate the destructor",this);

    _options_layout->addWidget(_options_protect_header);
    _options_layout->addWidget(_options_default_consturctor);
    _options_layout->addWidget(_options_default_destructor);
    _options_groupbox->setLayout(_options_layout);


    //============================  COMMENTS  ================================
    _comments_groupbox = new QGroupBox("Add comments");
    _comments_layout = new QVBoxLayout;
    _comments_groupbox->setCheckable(true);
    _comments_groupbox->setChecked(false);

    _comments_author = new QLineEdit;

    _comments_creation_date = new QDateEdit(QDate::currentDate());

    _comments_class_role = new QTextEdit;


    _comments_form_layout = new QFormLayout;
    _comments_form_layout->addRow("&Author",_comments_author);
    _comments_form_layout->addRow("&Creation date",_comments_creation_date);
    _comments_form_layout->addRow("&Class role",_comments_class_role);

    _comments_layout->addLayout(_comments_form_layout);
    _comments_groupbox->setLayout(_comments_layout);

    //========================================================================

    //   http://doc.qt.io/qt-5/qtwidgets-layouts-basiclayouts-example.html
    //   http://stackoverflow.com/questions/31290792/how-to-change-the-caption-of-a-button-in-a-qdialogbuttonbox

    _button_box = new QDialogButtonBox(QDialogButtonBox::Ok|
                                       QDialogButtonBox::Cancel);

    _button_box->button(QDialogButtonBox::Ok)->setText("Generate");
    _button_box->button(QDialogButtonBox::Ok)->setToolTip("Generate the code");

    _button_box->button(QDialogButtonBox::Cancel)->setText("Quit");

    QObject::connect(_button_box,SIGNAL(accepted()),this,SLOT(code_generater()));
    QObject::connect(_button_box,SIGNAL(rejected()),qApp,SLOT(quit()));


    //===============ESSENTAIL LAYOUT DONT TOUCH =============================
    _grid->addWidget(_options_groupbox,2,0);
    _grid->addWidget(_definition_groupbox,1,0);
    _grid->addWidget(_comments_groupbox,3,0);
    _grid->addWidget(_button_box,4,0);
    setLayout(_grid);
    //========================================================================

}


void Main_Window::code_generater()
{
    QString code;


    code +="\n /* \n";

    if(_comments_author->text().isEmpty() == false)
    {
        code += "\n Author :" + _comments_author->text() + "";
    }

    if (_comments_groupbox->isChecked())
    {
        QString _comments_creation_date_toString = _comments_creation_date->date().toString("dd/MM/yyyy");
        code += "\n Creation date :" + _comments_creation_date_toString + "";
    }


    if (_comments_class_role->toPlainText().operator !=(""))
    {
        code += "\n class role : " + _comments_class_role->toPlainText() + "";
    }

    //code += "\n class role : " + _comments_class_role->toPlainText() + "";

    code += "\n \n */";
    code += "\n ";


    if (_options_protect_header->isChecked())
    {
        code += "\n #ifndef " + _definition_name->text() + "_H"; // #ifndef CLASSNAME_H
        code += "\n #define " + _definition_name->text() + "_H"; // #define CLASS_H
    }

    // class CLASSNAME : public PARENTCLASSNAME
    code += "\n \n class " + _definition_name->text() + "";
    if (_definition_mother_class->isModified())
    {
        code += " : public " + _definition_mother_class->text() + "";
    }
    code += "\n { \n \n \n";


    if(_options_default_consturctor->isChecked() || _options_default_destructor->isChecked())
    {
        code += " public : ";
        if (_options_default_consturctor->isChecked())
        {
            code += "\n " + _definition_name->text() + " ();" ;
        }

        if (_options_default_destructor->isChecked())
        {
            code += "\n ~" + _definition_name->text() + " ();" ;
        }
    }

    code += "\n }; ";
    if (_options_protect_header->isChecked())
    {
        code += "\n \n #endif //" + _definition_name->text() + " " ;
    }

    Code_Viewer *view = new Code_Viewer(code,this);
    view->exec();
}
