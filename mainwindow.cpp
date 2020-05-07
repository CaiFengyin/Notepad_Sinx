#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newwindow.h"
#include  <QDialog>      //对话框
#include  <QMessageBox>  //问题对话框
#include  <QFile>       //文件类
#include  <QFileDialog> //文件对话框
#include  <QDateTime>   //日期类
#include  <QLabel>       //标签类
#include  <QTextCursor> //光标类
#include  <QFontDialog> //字体对话框
#include  <QFont>
#include  <QMouseEvent>  //鼠标事件
#include  <QTextCursor>
#include  <QTextLayout>
#include  <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置窗口标题
    setWindowTitle("_Notepad_");
    setWindowIcon(QIcon(":/image/notepad.png"));    //设置图标
    fileStatus  = false;        // 文件状态初始化为false,出于未保存状态
    label = new QLabel(this);   //新建标签对象
    //将当前标签添加到状态栏上,从右往左添加
    ui->statusBar->addPermanentWidget(label);
    ui->statusBar->setVisible(true);
    connect(ui->textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(cursorChanged()));



}

MainWindow::~MainWindow()
{
    delete  ui;
    delete  newWin;
}
 //1.新建文件：DONE
void MainWindow::on_action_Ctrl_N_triggered()
{


    //判断当前文本编辑区是否有内容，若有内容且内容未保存 则提示用户是否选择保存
    if(false == ui->textEdit->document()->isEmpty() && false == fileStatus)
    {
          QMessageBox msgBox;

          msgBox.setText("提示:文件未保存！");
          msgBox.setInformativeText("是否保存当前文件?");
          msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
          msgBox.setDefaultButton(QMessageBox::Save);
          msgBox.setButtonText(QMessageBox::Save,"保存");
          msgBox.setButtonText(QMessageBox::Discard,"不保存");
          msgBox.setButtonText(QMessageBox::Cancel,"取消");
          int ret = msgBox.exec();

          switch (ret)
          {
            case QMessageBox::Save:     //点击Save按钮保存文件
                                 {
              QFile file;
              QString text = ui->textEdit->toPlainText();
              filePath =  QFileDialog::getSaveFileName(this, tr("Save File"),
                                            "../untitled.txt",
                                            tr("Text files(*.txt)"));
              file.setFileName(filePath);
              file.open(QIODevice::WriteOnly);
              file.write(text.toUtf8());
              file.close();
              fileStatus = true;   //保存后文件状态置为true
              break;
             }

            case QMessageBox::Discard:
                // Don't Save was clicked
                   ui->textEdit->clear();   //  清空编辑区的内容
                   fileStatus = false;
                 break;
            case QMessageBox::Cancel:
                // Cancel was clicked
                break;
            default:
                // should never be reached
                break;
          }

    }
    else {//若没有内容或者内容已经保存过，则清空当前文本编辑区
        ui->textEdit->clear();
    }


}


//2.打开文件：DONE
void MainWindow::on_action_Ctrl_O_triggered()
{
     //若当前编辑内容为空或文件已经保存可以打开文件
   if( false == ui->textEdit->document()->isEmpty() || fileStatus == true)
    {       //选择文件路径
            filePath =  QFileDialog::getOpenFileName(
                                          this,
                                          "Open file",
                                          "../",
                   " Source code(*.c *.cpp *.h);;Txt(*.txt *.docx *.xls);;All(*.*)");
            //打开文件
            QFile file(filePath);
            file.open(QIODevice::ReadOnly);
            QByteArray text;//QByteArray t ;
            while(!file.atEnd())
                   text += file.readLine();
            //QString QString::fromLocal8Bit(const QByteArray &str)
            //QByteArray QString::toLocal8Bit() const
           ui->textEdit->setText(QString::fromLocal8Bit(text.data()));
           file.close();
   }
   else{    //未保存则先询问是否保存
           QMessageBox msgBox;
           msgBox.setInformativeText("是否保存当前文件?");
           msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
           msgBox.setDefaultButton(QMessageBox::Save);
           msgBox.setButtonText(QMessageBox::Save,"保存");
           msgBox.setButtonText(QMessageBox::Discard,"不保存");
           msgBox.setButtonText(QMessageBox::Cancel,"取消");
           int ret = msgBox.exec();
           switch (ret)
           {
             case QMessageBox::Save:     //点击Save按钮保存文件
                                  {
               QFile file;
               QString text = ui->textEdit->toPlainText();
               filePath =  QFileDialog::getSaveFileName(this, tr("Save File"),
                                             "../untitled.txt",
                                             tr("Text files(*.txt)"));
               file.setFileName(filePath);
               file.open(QIODevice::WriteOnly);
               file.write(text.toUtf8());
               file.close();
               fileStatus = true;   //保存后文件状态置为true
               break;
              }

             case QMessageBox::Discard:
                 // Don't Save was clicked
                    ui->textEdit->clear();   //  清空编辑区的内容
                    fileStatus = false;
                  break;
             case QMessageBox::Cancel:
                 // Cancel was clicked
                 break;
             default:
                 // should never be reached
                 break;
       }

   }

}
//3.保存：DONE
void MainWindow::on_action_Ctrl_S_triggered()
{
    QFile file;
    QString text = ui->textEdit->toPlainText(); //  获取编辑区内容
    filePath =  QFileDialog::getSaveFileName(this, tr("Save File"),
                                  "../untitled.txt",
                                  tr("Source code(*.c *.cpp *.h);;Txt(*.txt *.docx *.xls);;All(*.*)"));
    file.setFileName(filePath);
    file.open(QIODevice::WriteOnly);
    file.write(text.toUtf8());
    file.close();
    fileStatus = true;  //  每次保存文件后将文件状态设置为true

}

//4.打开新窗口：DONE
void MainWindow::on_actionxinchuangkou_Ctrl_Shift_N_triggered()
{
    newWin = new MainWindow();
    newWin->show();
}

//5.另存为：DONE
void MainWindow::on_action_Ctrl_Shift_S_triggered()
{
    QFile file;
    QString text = ui->textEdit->toPlainText(); //  获取编辑区内容
    filePath =  QFileDialog::getSaveFileName(this, tr("Save  As..."),
                                  "../untitled.txt",
                                  tr("Source code(*.c *.cpp *.h);;Txt(*.txt *.docx *.xls);;All(*.*)"));
    file.setFileName(filePath);
    file.open(QIODevice::WriteOnly);
    file.write(text.toUtf8());

    file.close();

}

//6.点击推出按钮退出当前窗口：DONE
void MainWindow::on_action_Ctrl_E_triggered()
{
    //qApp->quit();退出整个程序，qApp是全局变量
      MainWindow::close();
}
//鼠标点击事件：DONE
void MainWindow::closeEvent ( QCloseEvent * e )
{
     //检测当前文件状态，若编辑区有内容且未保存则提示用户
    if( false == ui->textEdit->document()->isEmpty()  &&fileStatus == false )
    {
        QMessageBox msgBox;
        msgBox.setText("提示:文件未保存！");
        msgBox.setInformativeText("是否保存当前文件?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.setButtonText(QMessageBox::Save,"保存");
        msgBox.setButtonText(QMessageBox::Discard,"不保存");
        msgBox.setButtonText(QMessageBox::Cancel,"取消");
        int ret = msgBox.exec();
        switch (ret)
        {
          case QMessageBox::Save:     //点击Save按钮保存文件
                               {
            QFile file;
            QString text = ui->textEdit->toPlainText();
            filePath =  QFileDialog::getSaveFileName(this, tr("Save File"),
                                          "../untitled.txt",
                                          tr("Text files(*.txt)"));
            file.setFileName(filePath);
            file.open(QIODevice::WriteOnly);
            file.write(text.toUtf8());
            file.close();
            fileStatus = true;   //保存后文件状态置为true
             MainWindow::close();//再次点击关闭当前窗口
             e->accept();//阻止事件传播
            break;
           }

          case QMessageBox::Discard:
              // Don't Save was clicked
                 ui->textEdit->clear();   //  清空编辑区的内容
                 fileStatus = false;        //问题：点击不保存后，不能直接退出而是必须再次点击才能退出？
                  MainWindow::close();
                   e->accept();//阻止事件传播
               break;
          case QMessageBox::Cancel: //问题：点击取消后，不能直接退出而是必须保存或不保存才能退出？
                fileStatus = false; //点击取消按钮,文件仍为保存
                MainWindow::close();
                 e->ignore();//阻止事件传播
                break;
          default:
              // should never be reached

              break;
        }//switch结束

    }//if结束
}

//7.撤销：DONE
void MainWindow::on_action_Ctrl_Z_triggered()
{
    ui->textEdit->undo();
}
//8.恢复：DONE
void MainWindow::on_action_Ctrl_R_triggered()
{
    ui->textEdit->undo();
}

//9.复制：DONE
void MainWindow::on_action_Ctrl_C_triggered()
{
    ui->textEdit->copy();
}
//粘贴：DONE
void MainWindow::on_action_Ctrl_V_triggered()
{
    ui->textEdit->paste();
}
//10.剪切：DONE
void MainWindow::on_action_Ctrl_X_triggered()
{
    ui->textEdit->cut();
}

//11.查找：
void MainWindow::on_action_Ctrl_F_triggered()
{

}
//12.全选：DONE
void MainWindow::on_action_Ctrl_A_triggered()
{
    ui->textEdit->selectAll();
}
//13.日期：DONE
void MainWindow::on_action_F5_triggered()
{
    QDateTime currentDate = QDateTime::currentDateTime();
    QString current = currentDate.toString("yyyy.MM.dd hh:mm:ss ddd");
    ui->textEdit->append(current);//在光标处追加当前时间
}
//14.设置字体:DONE
void MainWindow::on_action_Font_triggered()
{
    bool isOk = true;
    QFont font =  QFontDialog::getFont(&isOk);

    ui->textEdit->setFont(font);

}
//15.放大:
void MainWindow::on_action_Zoomin_triggered()
{
    ui->textEdit->zoomIn();
}
//15.缩小:
void MainWindow::on_action_Zoomout_triggered()
{
    ui->textEdit->zoomOut();
}

//17.状态栏:
void MainWindow::on_action_Status_triggered()
{
    if(ui->statusBar->isVisible() == true)
        ui->statusBar->setVisible(false);
    else
        ui->statusBar->setVisible(true);
}
//void MainWindow::mousePressEvent(QMouseEvent *event)
//{

//        // 如果是鼠标左键按下
//       if(event->button() == Qt::LeftButton)
//       {

//           QTextCursor cursor = ui->textEdit->textCursor();
//           int x = ui->textEdit->document()->blockCount();  //获取行
//           int y =  cursor.columnNumber();  //获取列
//           label->setText(QString("第%1行,%2列").arg(x).arg(y));

//       }
//        event->ignore();

//}
void MainWindow::cursorChanged()
{
    //获取光标所在行的行号
    //int rowNum = ui->textEdit->document()->blockCount();//blockCount()
     int rowNum = ui->textEdit->textCursor().blockNumber();
    //获取光标所在列的列号
    int colNum =  ui->textEdit->textCursor().columnNumber();

    //在状态栏显示光标位置
    label->setText(tr("第%1行 %2列").arg(rowNum+1).arg(colNum+1));

}


//关于记事本:
void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this,tr("关于_Notepad_"),tr("<h1>_Notepad_</h1>\n"
                                                 "Author: Sinx.\r\n"
                                                 "Created by:2020-04-07.\n"
                                                 "Copyright©  The author Sinx all rights reserved.\n"));
}








