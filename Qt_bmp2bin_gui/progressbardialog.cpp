#include "progressbardialog.h"
#include "ui_progressbardialog.h"

ProgressBarDialog::ProgressBarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressBarDialog), filename(), dir(), filesCompleted(0)
{
    ui->setupUi(this);
}

ProgressBarDialog::ProgressBarDialog(QString _filename, QString _dir, QWidget *parent) :
    QDialog(parent), ui(new Ui::ProgressBarDialog),
    filename(_filename), dir(_dir), filesCompleted(0)
{
    ui->setupUi(this);
}

ProgressBarDialog::~ProgressBarDialog()
{
    delete ui;
}

void ProgressBarDialog::threadUpdate()
{
    ++ filesCompleted;
    // now we need a total file count
    ui->progressBar->setValue(filesCompleted / fileCount);
}

bool ProgressBarDialog::generateBinDataFromBMP(const QString &dir, const QString &filename, int threshold)
{
    QFile bin(filename);
    if (!bin.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "Unable to generate " << filename << endl;
        return false;
    }

    for (int z = 1;; ++z)
    {
        QString bmp(dir + "/" + QString::number(z) + ".bmp");
        QFile f(bmp);
        // if there are no more files to be read
        if (!f.exists())
            break;

        QImage img(bmp, "BMP");
        if (img.isNull())
        {
            qDebug() << "Fail to read " << bmp << endl;
            continue;
        }

        // - 2 due to unknown issue
        int h = img.height() - 2;
        int w = img.bytesPerLine() / sizeof(QRgb);
        for (int y = 0; y < h; ++y)
        {
            const QRgb * scanline = (const QRgb *)img.scanLine(y);
            for (int x = 0; x < w; ++x)
            {
                const QRgb & px = scanline[x];
                if (qGray(px) < threshold)
                    continue;

                util_pixel_cross_platform_storage data;
                data.x = x; data.y = y; data.z = z;
                data.br = qRed(px); data.bg = qGreen(px); data.bb = qBlue(px);
                bin.write((const char *)&data, sizeof(util_pixel_cross_platform_storage));
            }
        }
    }
    bin.close();
    return true;
}
