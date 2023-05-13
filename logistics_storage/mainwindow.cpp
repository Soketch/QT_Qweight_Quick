#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QTextStream>
#include<QString>
#include<QList>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->InitFile();

    //退出
    connect(ui->BtnExit, &QPushButton::clicked, this, &QPushButton::close);

    //注册
    connect(ui->BtnCreate, &QPushButton::clicked, this, [=](){this->hide(); createA->show();});

    //登录  -- 判断(账号密码是否正确)
    Func->hide();
    connect(ui->BtnLogin, &QPushButton::clicked, this, &MainWindow::SlotsLoginOk);


}


void MainWindow::InitFile()
{
    // 应该有几个文件？   用户信息文件UserMsg     仓储物品文件StorageFile      入库信息记录文件PutSMsgFile    出库信息记录文件OutSMsgFile

    // 文件有的操作？   创建文件  文件是否存在  文件读取信息
    QStringList Files;
    Files<<"UserMsg"<<"StorageFile"<<"PutSMsgFile"<<"OutSMsgFile";
    for(int i=0; i<Files.size(); i++){
        QFile file(QString("%1.csv").arg(Files[i]));
        file.open(QIODevice::ReadWrite);
        file.close();
    }


}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotsLoginOk()
{
    bool flag = false;
    //打开文件  userMSG.xlsx
    QFile f("UserMsg.csv");  //读模式
    f.open(QIODevice::Text | QIODevice::ReadOnly);   //读写  文本打开方式
    QTextStream in(&f);
    QString line;
    QList<QString> fline;
    while (!in.atEnd()) {
        line = in.readLine();
        line = line.replace("\"","");
        fline = line.split('\t');
        if(ui->editUsername->text() == fline[0] && ui->editPassword->text() == fline[1]){
            //登录成功   -- 进入功能界面
            flag = true;
            this->hide();
            Func->show();
            break;
        }
    }
    f.close();
    if(flag != true){
        //登录失败
        QMessageBox::critical(this,"错误信息提示","账号或者密码错误");
        ui->editUsername->clear();
        ui->editPassword->clear();
    }
}

