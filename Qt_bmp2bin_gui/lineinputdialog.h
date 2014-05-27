#ifndef LINEINPUTDIALOG_H
#define LINEINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class LineInputDialog;
}

class LineInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LineInputDialog(QWidget *parent = 0);
    ~LineInputDialog();

    QString getUserInput();

private:
    Ui::LineInputDialog *ui;
};

#endif // LINEINPUTDIALOG_H
