#include "putswmsg.h"
#include "ui_putswmsg.h"
#include<QFile>
#include<QTextStream>
PutSWMsg::PutSWMsg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PutSWMsg)
{
    ui->setupUi(this);
    this->showMaximized();

    this->InitMSG();

    this->ShowMSG();


    connect(ui->BtnBack, &QPushButton::clicked, this, &PutSWMsg::SlotBackFunc);

}

void PutSWMsg::InitMSG()
{
    //表格初始化
    //table设置
    ui->tableWidget->setColumnCount(4);
    //设置表头
    QStringList headers;
    headers<<QStringLiteral("入库物品")<<QStringLiteral("放入位置")<<QStringLiteral("入库数量")<<QStringLiteral("入库时间");
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

void PutSWMsg::ShowMSG()
{
    //打开文件  把文件信息显示到表格中
    ui->tableWidget->setRowCount(0);
    QFile f("PutSMsgFile.csv");
    f.open(QIODevice::ReadOnly | QIODevice::Text);  //只读模式
    QTextStream  in(&f);
    QString line;
    QList<QString> fields;
    int row  = 0;
    while(!in.atEnd()){
        line = in.readLine();
        line = line.replace("\"","");
        fields = line.split('\t');
        int rowIndex = ui->tableWidget->rowCount();//当前表格的行数
        ui->tableWidget->insertRow(rowIndex);//在最后一行的后面插入一行
        for(int column = 0; column<fields.size();column++){
            ui->tableWidget->setItem(row, column, new QTableWidgetItem(fields[column])); //导入数据
        }
        row++;
    }
    f.close();
    ui->tableWidget->update();
}

PutSWMsg::~PutSWMsg()
{
    delete ui;
}

void PutSWMsg::SlotBackFunc()
{
    this->ShowMSG();
    emit SignalBackFunc();
}
