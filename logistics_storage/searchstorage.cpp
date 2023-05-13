#include "searchstorage.h"
#include "ui_searchstorage.h"
#include<QString>
#include<QDebug>
#include<QFile>
#include<QTextStream>
#include<QList>
SearchStorage::SearchStorage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchStorage)
{
    ui->setupUi(this);
    this->showMaximized();

    this->tableInit();
    //返回
    connect(ui->BtnBack,&QPushButton::clicked, this, &SearchStorage::SlotBackFunc);

    QList<QString> strList;
    strList<<"物品名称"<<"存放位置"<<"数量";
    ui->comboBox->addItems(strList);

    connect(ui->BtnSearch,&QPushButton::clicked, this, &SearchStorage::showMsg);
}

void SearchStorage::tableInit()
{
    //表格初始化
    //table设置
    ui->tableWidget->setColumnCount(4);
    //设置表头
    QStringList headers;
    headers<<QStringLiteral("物品名称")<<QStringLiteral("存放位置")<<QStringLiteral("物品数量")<<QStringLiteral("存放时间");
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

SearchStorage::~SearchStorage()
{
    delete ui;
}

void SearchStorage::SlotBackFunc()
{
    emit signalBackFunc();
}

void SearchStorage::showMsg()
{
    ui->tableWidget->clear();


    QFile f("StorageFile.csv");
    QTextStream in(&f);
    f.open(QIODevice::ReadOnly | QIODevice::Text);  //只读模式
    QString line;
    QList<QString> flines;
    int row  = 0;

    if(ui->comboBox->currentIndex() == 0){
        //按照名称查询
        while(!in.atEnd()){
            line = in.readLine();
            line = line.replace("\"","");
            flines = line.split('\t');
            if(flines[0] == ui->lineEdit->text()){
                int rowIndex = ui->tableWidget->rowCount();//当前表格的行数
                ui->tableWidget->insertRow(rowIndex);//在最后一行的后面插入一行
                for(int column = 0; column<flines.size();column++){
                    ui->tableWidget->setItem(row, column, new QTableWidgetItem(flines[column])); //导入数据
                }
                row++;
            }
            ui->tableWidget->update();
        }
    }
    else if(ui->comboBox->currentIndex() == 1){
        //按照位置查询
        while(!in.atEnd()){
            line = in.readLine();
            line = line.replace("\"","");
            flines = line.split('\t');
            if(flines[1] == ui->lineEdit->text()){
                int rowIndex = ui->tableWidget->rowCount();//当前表格的行数
                ui->tableWidget->insertRow(rowIndex);//在最后一行的后面插入一行
                for(int column = 0; column<flines.size();column++){
                    ui->tableWidget->setItem(row, column, new QTableWidgetItem(flines[column])); //导入数据
                }
                row++;
            }
            ui->tableWidget->update();
        }
    }
    else{
        //按照数量查询

        while(!in.atEnd()){
            line = in.readLine();
            line = line.replace("\"","");
            flines = line.split('\t');
            if(flines[2] == ui->lineEdit->text()){
                int rowIndex = ui->tableWidget->rowCount();//当前表格的行数
                ui->tableWidget->insertRow(rowIndex);//在最后一行的后面插入一行
                for(int column = 0; column<flines.size();column++){
                    ui->tableWidget->setItem(row, column, new QTableWidgetItem(flines[column])); //导入数据
                }
                row++;
            }
            ui->tableWidget->update();
        }
    }
    f.close();

}
