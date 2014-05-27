#include "lineinputdialog.h"
#include "ui_lineinputdialog.h"

LineInputDialog::LineInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LineInputDialog)
{
    ui->setupUi(this);
}

LineInputDialog::~LineInputDialog()
{
    delete ui;
}

QString LineInputDialog::getUserInput()
{
    return ui->lineEdit->text();
}
