#include "threadbmpreadprogress.h"

ThreadBmpReadProgress::ThreadBmpReadProgress(QString _filename, int _from, int _to, QString _dir, QObject *parent) :
    QThread(parent), filename(_filename), from(_from), to(_to), dir(_dir)
{
}

void ThreadBmpReadProgress::run()
{

}
