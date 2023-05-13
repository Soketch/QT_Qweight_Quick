#include "putsw.h"
#include "ui_putsw.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<QDateTime>
#include<QMessageBox>
PutSW::PutSW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PutSW)
{
    ui->setupUi(this);
    QDateTime time = QDateTime::currentDateTime();
    QString current_date =time.toString("yyyy.MM.dd hh:mm:ss");
    ui->LE_DateTime->setText(current_date);  //系统时间

    connect(ui->BtnBack, &QPushButton::clicked, this, &PutSW::on_BtnBack_clicked);

    connect(ui->BtnOK,&QPushButton::clicked, this, &PutSW::SaveFileMsg);
}

PutSW::~PutSW()
{
    delete ui;
}

void PutSW::on_BtnBack_clicked()
{
    emit SignalBackFunc();
}

void PutSW::SaveFileMsg()
{
    bool flag = false;
    if(ui->LE_ID->text() == "" || ui->LE_Num->text() == "" || ui->LE_Site->text() == ""){
        QMessageBox::information(this,"提示","请填写完整信息");
    }
    else if(ui->LE_Num->text().toInt()<0 || ui->LE_Num->text().toInt()>99999999){
        QMessageBox::critical(this,"错误","数值输入不合法");
    }
    else {
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
            if(ui->LE_ID->text() == fline[0] && ui->LE_Site->text() == fline[1]){
                //数量叠加   时间修改
                int num = fline[2].toInt() + ui->LE_Num->text().toInt();
                line = fline[0]+'\t'+fline[1]+'\t'+QString::number(num,10)+'\t'+ui->LE_DateTime->text();
                flag = true;

            }
            ary.append(line);  //列表追加形式
        }

        QFile f2("PutSMsgFile.csv");
        f2.open(QIODevice::Append | QIODevice::Text);
        QTextStream in2(&f2);
        QString s = ui->LE_ID->text()+'\t'+ui->LE_Site->text()+'\t'+ui->LE_Num->text()+'\t'+ui->LE_DateTime->text();
        in2<<s<<"\n";

        if(flag != true){
            ary.append(s);
        }
        f1.close();
        f2.close();

        QFile wf("StorageFile.csv");
        wf.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&wf);
        for(int i=0; i<ary.size(); i++){
            out<<ary[i]<<"\n";
        }
        wf.close();
        QMessageBox::information(this,"提示","保存成功");
    }
    //qDebug()<<ary<<ary.size();
    ui->LE_ID->clear();
    ui->LE_Num->clear();
    ui->LE_Site->clear();
}

//void PutSW::on_BtnOK_1_clicked()
//{
//    bool flag = false;
//    if(ui->LE_ID->text() == "" || ui->LE_Num->text() == "" || ui->LE_Site->text() == ""){
//        QMessageBox::information(this,"提示","请填写完整信息");
//    }
//    else if(ui->LE_Num->text().toInt()<0 || ui->LE_Num->text().toInt()>99999999){
//        QMessageBox::critical(this,"错误","数值输入不合法");
//    }
//    else {
//        QFile f1("StorageFile.csv");  //读模式
//        f1.open(QIODevice::Text | QIODevice::ReadOnly);   //读写  文本打开方式
//        QTextStream in(&f1);
//        QString line;
//        QList<QString> fline, ary;
//        while(!in.atEnd())
//        {

//            line = in.readLine();
//            line = line.replace("\"","");
//            fline = line.split('\t');
//            if(ui->LE_ID->text() == fline[0] && ui->LE_Site->text() == fline[1]){
//                //数量叠加   时间修改
//                int num = fline[2].toInt() + ui->LE_Num->text().toInt();
//                line = fline[0]+'\t'+fline[1]+'\t'+num+'\t'+ui->LE_DateTime->text();
//                flag = true;

//            }
//            ary.append(line);  //列表追加形式
//        }

//        QFile f2("PutSMsgFile.csv");
//        f2.open(QIODevice::Append | QIODevice::Text);
//        QTextStream in2(&f2);
//        QString s = ui->LE_ID->text()+'\t'+ui->LE_Site->text()+'\t'+ui->LE_Num->text()+'\t'+ui->LE_DateTime->text();
//        in2<<s<<"\n";

//        if(flag != true){
//            ary.append(s);
//        }
//        f1.close();
//        f2.close();

//        QFile wf("StorageFile.csv");
//        wf.open(QIODevice::WriteOnly | QIODevice::Text);
//        QTextStream out(&wf);
//        for(int i=0; i<ary.size(); i++){
//            out<<ary[i];
//        }
//        wf.close();
//    }

//    //qDebug()<<ary<<ary.size();
//    ui->LE_ID->clear();
//    ui->LE_Num->clear();
//    ui->LE_Site->clear();
//}
