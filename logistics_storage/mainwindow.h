#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<createwidget.h>
#include<storagefunction.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void InitFile();

    ~MainWindow();
public slots:
    void SlotsLoginOk();

private:
    Ui::MainWindow *ui;
    CreateWidget* createA = new CreateWidget;
    StorageFunction* Func = new StorageFunction;
};
#endif // MAINWINDOW_H
