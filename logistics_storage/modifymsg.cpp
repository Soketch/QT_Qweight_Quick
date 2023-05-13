#include "modifymsg.h"
#include "ui_modifymsg.h"
#include<QFile>
#include<QTextStream>
#include<QString>
#include<QList>
#include<QMessageBox>
ModifyMSG::ModifyMSG(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyMSG)
{
    ui->setupUi(this);
    this->showMaximized();
    this->Init();

    this->showAllMsg();
    connect(ui->tableWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(getItem(QModelIndex)));

    connect(ui->BtnBack, &QPushButton::clicked, this, &ModifyMSG::SlotBackFunc);

    connect(ui->BtnOk, &QPushButton::clicked, this,&ModifyMSG::SlotBtnOKMsg);
}

void ModifyMSG::Init()
{
    //表格初始化
        //table设置
        ui->tableWidget->setColumnCount(4);
        //设置表头
        QStringList headers;
        headers<<QStringLiteral("物品名称")<<QStringLiteral("存放位置")<<QStringLiteral("数量")<<QStringLiteral("入库时间");
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

void ModifyMSG::showAllMsg()
{
    //打开文件  把文件信息显示到表格中
    QFile f("StorageFile.csv");
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

ModifyMSG::~ModifyMSG()
{
    delete ui;
}

void ModifyMSG::getItem(const QModelIndex &index)
{
    QString ID = ui->tableWidget->model()->index(index.row(),0).data().toString(); //使用一个字符串接收
    ui->LE_ID->setText(ID);

    QString Num = ui->tableWidget->model()->index(index.row(),1).data().toString();
    ui->LE_Num->setText(Num);
    QString Site = ui->tableWidget->model()->index(index.row(),2).data().toString();
    ui->LE_Site->setText(Site);
    QString Date = ui->tableWidget->model()->index(index.row(),3).data().toString();
    ui->LE_Date->setText(Date);

    this->m_Count = ui->tableWidget->model()->index(index.row(),0).row();
    //qDebug()<<"count"<<this->m_Count;

}

void ModifyMSG::SlotBackFunc()
{
    emit signalBackFunc();
}

void ModifyMSG::SlotBtnOKMsg()
{
    //获取信息   修改表格

    ui->tableWidget->setItem(this->m_Count,0,new QTableWidgetItem(ui->LE_ID->text()));
    ui->tableWidget->setItem(this->m_Count,1,new QTableWidgetItem(ui->LE_Num->text()));
    ui->tableWidget->setItem(this->m_Count,2,new QTableWidgetItem(ui->LE_Site->text()));
    ui->tableWidget->setItem(this->m_Count,3,new QTableWidgetItem(ui->LE_Date->text()));
    ui->tableWidget->update();

    QList<QString> ary;
    QString s;
    for( int i=0; i<ui->tableWidget->rowCount(); i++){
        s = ui->tableWidget->item(i,0)->text()+'\t'
            +ui->tableWidget->item(i,1)->text()+'\t'
            +ui->tableWidget->item(i,2)->text()+'\t'
            +ui->tableWidget->item(i,3)->text();
        ary.append(s);
        //qDebug()<<s;
    }
    //qDebug()<<ary;
    QFile f("StorageFile.csv");
    QTextStream out(&f);
    f.open(QIODevice::Text | QIODevice::WriteOnly);
    for(int i=0;  i<ui->tableWidget->rowCount();i++){
        s = ui->tableWidget->item(i,0)->text()+'\t'
                +ui->tableWidget->item(i,1)->text()+'\t'
                +ui->tableWidget->item(i,2)->text()+'\t'
                +ui->tableWidget->item(i,3)->text();
        out<<s<<"\n";
    }
    QMessageBox::information(this,"提示","修改完成");
    f.close();

}
