#include "createwidget.h"
#include "ui_createwidget.h"
#include<QString>
#include<QFile>
#include<QTextStream>
#include<QList>
#include<QMessageBox>
CreateWidget::CreateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateWidget)
{
    ui->setupUi(this);

    //保存
    connect(ui->BtnOK,&QPushButton::clicked, this, &CreateWidget::SlotSave);

    //退出
    connect(ui->BtnExit, &QPushButton::clicked, this, &CreateWidget::close);
}

CreateWidget::~CreateWidget()
{
    delete ui;
}

void CreateWidget::SlotSave()
{
    bool flag = false;
    QFile f("UserMsg.csv");  //读模式
    f.open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Append);   //读写  文本打开方式
    QTextStream in(&f);
    QString line;
    QList<QString> fline;
    while (!in.atEnd()) {
        line = in.readLine();
        line = line.replace("\"","");
        fline = line.split('\t');
        if(ui->editUserName->text() == fline[0]){
            flag = true;  //找到相同账号
            break;
        }
    }
    QTextStream pf(&f);
    if(flag != true){
        line = ui->editUserName->text() + '\t' + ui->editPassWord->text();
        pf<<line<<'\n';
        //qDebug()<<line;
        QMessageBox::information(this,"提示","创建成功");
    }
    else {
        QMessageBox::warning(this,"提示","账号已经存在,不可重复创建");
    }


    f.close();
    ui->editUserName->clear();
    ui->editPassWord->clear();

}
