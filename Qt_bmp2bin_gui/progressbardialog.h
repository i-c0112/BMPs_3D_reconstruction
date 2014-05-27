#ifndef PROGRESSBARDIALOG_H
#define PROGRESSBARDIALOG_H

#include <QDialog>

namespace Ui {
class ProgressBarDialog;
}

class ProgressBarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressBarDialog(QWidget *parent = 0);
    ProgressBarDialog(QString _filename, QString _dir = QString(), QWidget *parent = 0);
    ~ProgressBarDialog();

public slots:
    // note that threads emit signals for every file reading completed
    // NOT percentage update
    void threadUpdate();

private:
    Ui::ProgressBarDialog *ui;
    QString filename;
    QString dir;
    // note that this is not equal to percentage
    int filesCompleted;
    // the dialog is responsible for counting all existing file (file names follow certain rule)
    int fileCount;

    //
    // i-c0112 14/05/27: move this from ThreadBmpReadProgress because it is the dialog that should manage the overall file generation

    // read all possible bmp in "dir" and generate binary data file "filename" (pixels whose gray values are below threshold will not be stored!)
    // syntax of bmp files: "index".bmp (index begins at 1)
    // returns false if file cannot be generated, otherwise true is returned

    // i-c0112 14/5/27: this should create child processes to make the generation faster. And use data parallelism to speed up the for loop
    //

    bool generateBinDataFromBMP(const QString & dir, const QString & filename, int threshold);
};
};

#endif // PROGRESSBARDIALOG_H
