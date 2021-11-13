#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AboutDialog.h"
#include "ChooseElementTypeDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;
               }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionaboutThis_triggered();

    void on_pushButton_clicked();

    void on_newFile_triggered();

private:
    Ui::MainWindow *ui;
    AboutDialog *aboutDialog;//前面加了Ui::会报错
    ChooseElementTypeDialog *chooseElementTypeDialog;
};
#endif // MAINWINDOW_H
