#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "AboutDialog.h"
#include "ChooseElementTypeDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionaboutThis_triggered()
{
    //新建窗口对象，其中的this表示该窗口的父对象是MainWindow。
    //这就使得在销毁MainWindow时也会销毁子对象，即该窗口对象。
    aboutDialog = new AboutDialog(this);
    //Model属性决定了show()应该弹出的dialog设为模态还是非模态
    //默认为false，非模态
    //把这个属性设置为true就相当于设置QWeight::windowmodality为Qt::ApplicationModel
    //执行exec()忽略这个Model属性，并且把弹出的dialog()设置为模态，
    aboutDialog->setModal(true);
    aboutDialog->show();
}


void MainWindow::on_pushButton_clicked()
{
    chooseElementTypeDialog = new ChooseElementTypeDialog(this);
    chooseElementTypeDialog->setModal(true);
    chooseElementTypeDialog->show();
}


void MainWindow::on_newFile_triggered()
{

}

