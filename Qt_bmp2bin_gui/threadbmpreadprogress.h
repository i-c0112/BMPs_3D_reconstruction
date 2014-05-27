#ifndef THREADBMPREADPROGRESS_H
#define THREADBMPREADPROGRESS_H

#include <QThread>

// A thread handle for loop in a data parallelism way
class ThreadBmpReadProgress : public QThread
{
    Q_OBJECT
public:
    ThreadBmpReadProgress(QString _filename, int _from, int _to, QString _dir = QString(), QObject *parent = 0);

signals:
    void fileComplete();

public slots:

protected:
    virtual void run();

private:
    QString filename;
    int from;
    int to;
    QString dir;

#endif // THREADBMPREADPROGRESS_H
