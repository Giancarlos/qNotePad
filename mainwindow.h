#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public slots:
    void openFile();
    void saveFile();
    void saveFileAs();
    void openAbout();
    void textChanged();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QString fileLocation;
    QString fileContents;
};

#endif // MAINWINDOW_H
