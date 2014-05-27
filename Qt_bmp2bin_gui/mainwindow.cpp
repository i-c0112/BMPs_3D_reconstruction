#include <QFile>
#include <QImage>
#include <QDebug>
#include <QFileDialog>
#include "mainwindow.h"
#include "lineinputdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // setup actions
    actNew = new QAction("&New", this);
    actNew->setShortcut(QKeySequence::New);
    actNew->setStatusTip("Create a new construction.");
    connect(actNew, SIGNAL(triggered()), SLOT(menuActionNew()));

    // setup menu
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(actNew);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::menuActionNew()
{
    // popup dialog to ask the user for a file name
    LineInputDialog * textDialog = new LineInputDialog(this);

    // exec run dialog as modal and by default dialog is set to application modal
    int result = textDialog->exec();
    // waiting for input(exec is synchronized)
    // ..

    QString newFileName;
    if (result == QDialog::Accepted)
    {
        // retrieve the user input
        newFileName = textDialog->getUserInput();
    }
    // not sure if exec close the dialog when done.
    // in most cases, the dialog is just hidden.
    textDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    textDialog->close();

    if (result == QDialog::Rejected)
        return;

    // if yes popup QFileDialog for a dir containing BMPs to read
    QString dir;
    dir = QFileDialog::getExistingDirectory(this, "Select where the BMPs are located.", "D:/Coding/reconstruct/01/sample");
    if (dir.isNull())
        return;

    // if yes popup another dialog to show progress bar and create a QThread for IO


}
