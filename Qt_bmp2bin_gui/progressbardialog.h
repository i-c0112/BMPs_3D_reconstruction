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

    // should never put process in ctor so need a button or some event to run the dialog
    void start();

private:
    Ui::ProgressBarDialog *ui;
    QString filename;
    QString dir;
    // note that this is not equal to percentage
    qint16 filesCompleted;
    // the dialog is responsible for counting all existing file (file names follow certain rule)
    qint16 fileCount;

    // i-c0112 14/05/27: move this from ThreadBmpReadProgress because it is the dialog that should manage the overall file generation
    // i-c0112 14/5/27: this should create child processes to make the generation faster. And use data parallelism to speed up the for loop

    // read all possible bmp in "dir" and generate binary data file "filename" (pixels whose gray values are below threshold will not be stored!)
    // syntax of bmp files: "index".bmp (index begins at 1)
    // returns false if file cannot be generated, otherwise true is returned

    // @param dir: QString. where the files to be read.
    // @param filename: QString. where the output file will be.
    // @param threshold: qint8. thresholding accordint to this value.

    bool generateBinDataFromBMP(const QString & dir, const QString & filename, qint8 threshold);
};

#endif // PROGRESSBARDIALOG_H
