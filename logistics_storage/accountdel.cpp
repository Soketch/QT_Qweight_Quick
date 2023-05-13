#include "accountdel.h"
#include "ui_accountdel.h"
#include<QFile>
#include<QTextStream>
#include<QList>
#include<QString>
#include<QMessageBox>

AccountDel::AccountDel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountDel)
{
    ui->setupUi(this);
    this->tableInit();

    this->showMSG();

    connect(ui->BtnBack,&QPushButton::clicked, this,&AccountDel::slotBackFunc );

    connect(ui->BtnOK,&QPushButton::clicked, this,&AccountDel::slotBtnOK);
}

void AccountDel::tableInit()
{
    //表格初始化
    //table设置
    ui->tableWidget->setColumnCount(1);
    //设置表头
    QStringList headers;
    headers<<QStringLiteral("账号");
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    //列宽自动填满表格
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //设置表头颜色
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    //设置相邻行颜色交替显示
    ui->tableWidget->setAlternatingRowColors(true);
    //单行选中
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->update();
}

void AccountDel::showMSG()
{
    ui->tableWidget->setRowCount(0);
    QFile f("UserMsg.csv");  //读模式
    f.open(QIODevice::Text | QIODevice::ReadOnly);   //读写  文本打开方式
    QTextStream in(&f);
    QString line;
    QList<QString> fline;
    int row = 0;
    while (!in.atEnd()) {
        line = in.readLine();
        line = line.replace("\"","");
        fline = line.split('\t');
        int rowIndex = ui->tableWidget->rowCount();//当前表格的行数
        ui->tableWidget->insertRow(rowIndex);//在最后一行的后面插入一行
        for(int column = 0; column<fline.size();column++){
            ui->tableWidget->setItem(row, column, new QTableWidgetItem(fline[0])); //导入数据
        }
        row++;
    }
    f.close();
}

AccountDel::~AccountDel()
{
    delete ui;
}

void AccountDel::slotBackFunc()
{
    emit signalBackFunc();
}

void AccountDel::slotBtnOK()
{

    bool flag = true;
    QFile f("UserMsg.csv");  //读模式
    f.open(QIODevice::Text | QIODevice::ReadOnly);   //读写  文本打开方式
    QTextStream in(&f);
    QString line;
    QList<QString> fline, ary;
    while (!in.atEnd()) {
        line = in.readLine();
        line = line.replace("\"","");
        fline = line.split('\t');
        if(ui->lineEditUN->text() == fline[0] && ui->lineEditPW->text() == fline[1]){
            flag = false;
            continue;
        }
        ary.append(line);
    }
    f.close();

    if(flag == false){
        QFile f2("UserMsg.csv");  //读模式
        f.open(QIODevice::Text | QIODevice::WriteOnly);   //读写  文本打开方式
        QTextStream in2(&f);
        for(int i=0; i<ary.size();i++){
            in2<<ary[i]<<"\n";
        }
        f2.close();
    }
    else {
        QMessageBox::warning(this,"提示","输入错误");
    }
    this->showMSG();
}
