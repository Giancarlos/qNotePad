#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

//*************************
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileLocation = "";
}

//*************************
MainWindow::~MainWindow()
{
    delete ui;
}

//*************************
void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"));

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString content = file.readAll();

    file.close();

    ui->textEdit->setText(content);
    fileLocation = fileName;
    MainWindow::setWindowTitle("qNotePad - " + fileName);
}

//*************************
void MainWindow::saveFile()
{
    // If no file location set, use save as function instead.
    if(fileLocation == "")
    {
        saveFileAs();
        return;
    }

    QFile file(fileLocation);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    fileContents = ui->textEdit->toPlainText();
    out << fileContents;
    file.close();
    fileContents = "";
    MainWindow::setWindowTitle("qNotePad - " + fileLocation);
}

//*************************
void MainWindow::saveFileAs()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"));
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    fileContents = ui->textEdit->toPlainText();
    out << fileContents;
    file.close();
    fileContents = "";
    fileLocation = filename;
    MainWindow::setWindowTitle("qNotePad - " + fileLocation);
}

//*************************
void MainWindow::openAbout()
{
    About *a = new About();
    a->show();
}

//*************************
void MainWindow::textChanged()
{
    // If there is no file location, let user know they haven't
    // saved their data yet.
    if(fileLocation == "")
    {
        MainWindow::setWindowTitle("qNotePad - Unsaved Data");
        return;
    }

    MainWindow::setWindowTitle("qNotePad - " + fileLocation + "*");
}
