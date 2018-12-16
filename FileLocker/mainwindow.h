#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTime>
#include <QFile>
#include <QFileDialog>
#include"titlebar.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();

    void Setupshowmodel(int i);

    void on_actionwhite_triggered();

    void on_actiongray_triggered();

    void on_actionblue_triggered();

    void on_actionred_triggered();

    void on_actionblack_triggered();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
