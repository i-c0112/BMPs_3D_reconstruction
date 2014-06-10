#include <QImage>
#include <QDebug>
#include "threadbmpreadprogress.h"
#include "struct_pixel.h"

ThreadBmpReadProgress::ThreadBmpReadProgress(QFile *_file, int _from, int _to, qint8 _threshold = 112, QString _dir, QObject *parent) :
    QThread(parent), file(_file), from(_from), to(_to), dir(_dir), threshold(_threshold)
{
}

void ThreadBmpReadProgress::run()
{
    qDebug() << "from: " << from << "; to: " << to << "; file.openMode(): " << file->openMode() << endl;

    // the actual file read/write is multi-threaded for time efficiency issue
    for (qint16 z = from; z <= to; ++z)
    {
        QString bmp = QString("%1/%2.bmp").arg(dir).arg(QString::number(z));
        //qDebug() << bmp << endl;
        QImage img(bmp, "BMP");
        if (img.isNull())
        {
            qDebug() << "Fail to read " << bmp << endl;
            continue;
        }

        // - 2 due to unknown issue
        qint16 h = img.height() - 2;
        qint16 w = img.bytesPerLine() / sizeof(QRgb);

        for (qint16 y = 0; y < h; ++y)
        {
            const QRgb * scanline = (const QRgb *)img.scanLine(y);
            for (qint16 x = 0; x < w; ++x)
            {
                const QRgb & px = scanline[x];

                //qDebug() << QString("threadshold=(%1), px=(%2)\n").arg(threshold).arg(qGray(px));
                if (qGray(px) < threshold)
                    continue;

                util_pixel_cross_platform_storage data;
                data.x = x; data.y = y; data.z = z;
                data.br = qRed(px); data.bg = qGreen(px); data.bb = qBlue(px);

                if (file->write((const char *)&data, sizeof(util_pixel_cross_platform_storage)) == -1)
                {
                    qDebug() << "Failed to write data:!\n";
                }
            }
        }
        emit fileRead();
    }
}
