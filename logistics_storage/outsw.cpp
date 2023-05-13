#include "outsw.h"
#include "ui_outsw.h"
#include<QFile>
#include<QTextStream>
#include<QDateTime>
#include<QMessageBox>
#include<QList>
#include<QString>
OutSW::OutSW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutSW)
{
    ui->setupUi(this);
    this->showMaximized();

    this->Init();
    this->showAllMsg();

    connect(ui->tableWidget_4, SIGNAL(doubleClicked(QModelIndex)),this,SLOT(getItem(QModelIndex)));

    //完成
    connect(ui->BtnOK_4, &QPushButton::clicked, this, &OutSW::OutOKMsg);
    //返回
    connect(ui->BtnBack_4,&QPushButton::clicked, this, &OutSW::SlotBackFunc);
}

void OutSW::Init()
{
    //表格初始化
    //table设置
    ui->tableWidget_4->setColumnCount(4);
    //设置表头
    QStringList headers;
    headers<<QStringLiteral("物品名称")<<QStringLiteral("存放位置")<<QStringLiteral("物品数量")<<QStringLiteral("入库时间");
    ui->tableWidget_4->setHorizontalHeaderLabels(headers);

    //列宽自动填满表格
    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //设置表头颜色
    ui->tableWidget_4->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    //设置相邻行颜色交替显示
    ui->tableWidget_4->setAlternatingRowColors(true);
    //单行选中
    ui->tableWidget_4->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_4->update();

    QDateTime time = QDateTime::currentDateTime();
    QString current_date =time.toString("yyyy.MM.dd hh:mm:ss");
    ui->LE_Date_4->setText(current_date);

}

void OutSW::showAllMsg()
{

    //打开文件  把文件信息显示到表格中
    ui->tableWidget_4->setRowCount(0);
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
        int rowIndex = ui->tableWidget_4->rowCount();//当前表格的行数
        ui->tableWidget_4->insertRow(rowIndex);//在最后一行的后面插入一行
        for(int column = 0; column<fields.size();column++){
            ui->tableWidget_4->setItem(row, column, new QTableWidgetItem(fields[column])); //导入数据
        }
        row++;
    }
    f.close();
    ui->tableWidget_4->update();
}


OutSW::~OutSW()
{
    delete ui;
}

void OutSW::getItem(const QModelIndex &index)
{
    this->m_count = ui->tableWidget_4->model()->index(index.row(),0).row();
    QString ID = ui->tableWidget_4->model()->index(index.row(),0).data().toString(); //使用一个字符串接收
    ui->LE_ID_4->setText(ID);

    QString Site = ui->tableWidget_4->model()->index(index.row(),1).data().toString();
    ui->LE_Site_4->setText(Site);

    QString Num = ui->tableWidget_4->model()->index(index.row(),2).data().toString();
    this->temp = Num.toInt();
    ui->LE_Num_4->setText(Num);

    QString Date = ui->tableWidget_4->model()->index(index.row(),3).data().toString();
    ui->LE_Date_4->setText(Date);
    ui->LE_ID_4->setReadOnly(true);
    ui->LE_Site_4->setReadOnly(true);
    ui->LE_Date_4->setReadOnly(true);
}

void OutSW::SlotBackFunc()
{
    this->showAllMsg();
    emit signalBackFunc();
}

void OutSW::OutOKMsg()
{
    bool flag = false;
    QFile f1("StorageFile.csv");  //读模式
    f1.open(QIODevice::Text | QIODevice::ReadOnly);   //读写  文本打开方式
    QTextStream in(&f1);
    QString line;
    QList<QString> fline, ary;

    while(!in.atEnd())
    {
        line = in.readLine();
        line = line.replace("\"","");
        fline = line.split('\t');
        if(ui->LE_Num_4->text().toInt() > fline[2] || ui->LE_Num_4->text().toInt()<0 ){
            QMessageBox::critical(this,"错误提示","输入错误");
            return;
        }
        if(ui->LE_ID_4->text() == fline[0] && ui->LE_Site_4->text() == fline[1]){
            //数量修改   时间修改
            int num = fline[2].toInt() - ui->LE_Num_4->text().toInt();
            line = fline[0]+'\t'+fline[1]+'\t'+QString::number(num,10)+'\t'+ui->LE_Date_4->text();
            flag = true;
        }
        ary.append(line);  //列表追加形式
    }

    QFile f2("OutSMsgFile.csv");
    f2.open(QIODevice::Append | QIODevice::Text);
    QTextStream in2(&f2);
    QString s = ui->LE_ID_4->text()+'\t'+ui->LE_Site_4->text()+'\t'+ui->LE_Num_4->text()+'\t'+ui->LE_Date_4->text();
    in2<<s<<"\n";

    f1.close();
    f2.close();

    QFile wf("StorageFile.csv");
    wf.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&wf);
    for(int i=0; i<ary.size(); i++){
        out<<ary[i]<<"\n";

    }
    wf.close();
    if(flag == true){
        QMessageBox::information(this,"提示","出库成功");
    }

    this->showAllMsg();
}





