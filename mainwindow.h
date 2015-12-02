#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "models.h"
#include "controller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool attachController(control::Controller *controller);


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    control::Controller *controller;
};

#endif // MAINWINDOW_H
