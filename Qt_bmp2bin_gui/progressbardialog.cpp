#include <QDebug>
#include "progressbardialog.h"
#include "threadbmpreadprogress.h"
#include "ui_progressbardialog.h"

ProgressBarDialog::ProgressBarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressBarDialog),
    filename(), dir(), filesCompleted(0), fileCount(0)
{
    ui->setupUi(this);
}

ProgressBarDialog::ProgressBarDialog(QString _filename, QString _dir, QWidget *parent) :
    QDialog(parent), ui(new Ui::ProgressBarDialog),
    filename(_filename), dir(_dir), filesCompleted(0)
{
    ui->setupUi(this);

    // init progress bar display
    ui->progressBar->setValue(0);

    connect(ui->pushButton, SIGNAL(clicked()), SLOT(start()));
}

ProgressBarDialog::~ProgressBarDialog()
{
    delete ui;
}

void ProgressBarDialog::threadUpdate()
{
    ++ filesCompleted;
    // now we need a total file count
    ui->progressBar->setValue(double(filesCompleted) / fileCount * 100.0);

    setAttribute(Qt::WA_DeleteOnClose, true);
    if (filesCompleted >= fileCount)
        done(QDialog::Accepted);
}

void ProgressBarDialog::start()
{
    ui->pushButton->setEnabled(false);
    generateBinDataFromBMP(dir, filename, 112);
}

bool ProgressBarDialog::generateBinDataFromBMP(const QString &dir, const QString &filename, qint8 threshold)
{
    QFile *bin = new QFile(filename, this);
    if (!bin->open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "Unable to generate " << filename << endl;
        return false;
    }

    for (qint16 z = 1;; ++z)
    {
        QString bmp(dir + "/" + QString::number(z) + ".bmp");
        //qDebug() << "counting files. checking existence of " << bmp << endl;
        QFile f(bmp);
        // if there are no more files to be read
        if (!f.exists())
            break;

        // if exists increase var fileCount
        ++fileCount;
    }
    qDebug() << "fileCount=" << fileCount << "; fileComplete=" << filesCompleted << endl;

    // @todo
    // i-c0112 14/05/30:
    //
    // create multi thread to implement data paralellism and read/write data
    // remember pass the QFile varaible's address to the child threads' ctor to tell them where to write to.
    // connect child threads' signal "fileRead" to this dialog's slot "threadUpdate"

    // it doesnt have the default ctor so seperated construction is required
    const qint8 n = 2;
    qint16 idx = 1;
    ThreadBmpReadProgress * pThreads[n];
    for (qint8 i = 0; i < n; ++ i)
    {
        qint16 next = idx + fileCount / n - 1;
        pThreads[i] = new ThreadBmpReadProgress(bin, idx, next, threshold, dir, this);
        idx = next;
        connect(pThreads[i], &ThreadBmpReadProgress::fileRead, this, &ProgressBarDialog::threadUpdate);
        // [from_1, to_1] -> [from_2=to_1+1, to_2]
        ++idx;
        pThreads[i]->start();
        qDebug() << "thread run() called: " << i << endl;
    }

    return true;
}
