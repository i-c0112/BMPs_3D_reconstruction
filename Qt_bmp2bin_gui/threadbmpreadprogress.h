#ifndef THREADBMPREADPROGRESS_H
#define THREADBMPREADPROGRESS_H

#include <QThread>
#include <QFile>

// A thread handle for loop in a data parallelism way
class ThreadBmpReadProgress : public QThread
{
    Q_OBJECT

public:
    ThreadBmpReadProgress(QFile *_file, int _from, int _to, qint8 _threshold, QString _dir = QString(), QObject *parent = 0);

    virtual void run();

signals:
    // signales whenever this thread finish a file reading and processing.
    void fileRead();

private:
    // file is not copy-able, so need a telepo.... pointer here.
    QFile *file;
    int from;
    int to;
    QString dir;
    qint8 threshold;
};

#endif // THREADBMPREADPROGRESS_H
