#include <QAPPlication>
#include "GLWidget.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    GLWidget glw;
    glw.show();
    return app.exec();
}
