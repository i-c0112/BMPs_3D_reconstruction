#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "struct_pixel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMenu * fileMenu;
    QAction * actNew;
    QAction * actOpen;

private slots:
    void menuActionNew();
};

#endif // MAINWINDOW_H
