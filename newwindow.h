#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"

namespace Ui {
class NewWindow;
}

class NewWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewWindow(QWidget *parent = nullptr);
    ~NewWindow();

private:
    Ui::NewWindow *ui;
    MainWindow m;
};

#endif // NEWWINDOW_H
