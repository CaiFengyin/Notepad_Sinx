#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QLabel>
#include  "fontset.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_action_Ctrl_N_triggered();

    void on_action_Ctrl_O_triggered();

    void on_action_Ctrl_S_triggered();

    void on_actionxinchuangkou_Ctrl_Shift_N_triggered();

    void on_action_Ctrl_Shift_S_triggered();

    void on_action_Ctrl_E_triggered();
    void on_action_Ctrl_Z_triggered();

    void on_action_Ctrl_C_triggered();

    void on_action_Ctrl_V_triggered();

    void on_action_Ctrl_X_triggered();

    void on_action_Ctrl_F_triggered();

    void on_action_Ctrl_A_triggered();

    void on_action_F5_triggered();

    void on_action_About_triggered();

//    void on_action_triggered();
//    void on_action_Ctrl_R_triggered();

    void on_action_Font_triggered();

    void on_action_Status_triggered();

    void on_action_Zoomin_triggered();

    void on_action_Zoomout_triggered();

    void on_action_Ctrl_R_triggered();

    void cursorChanged(); //获取光标位置信息
protected :
    void closeEvent(QCloseEvent *event);


private:
    Ui::MainWindow *ui;
    QString filePath;              //文件路径
    bool    fileStatus;          // 文件状态
    MainWindow *newWin;         //新窗口指针

    QLabel  *label;             //标签,显示鼠标的相对坐标



};

#endif // MAINWINDOW_H
