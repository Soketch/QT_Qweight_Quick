#include "storagefunction.h"
#include "ui_storagefunction.h"

StorageFunction::StorageFunction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StorageFunction)
{
    ui->setupUi(this);
    this->showMaximized();
    connect(ui->BtnExit,&QPushButton::clicked, this, &StorageFunction::close);

    //入库
    connect(ui->BtnPut,&QPushButton::clicked, this, [=](){this->hide(); puts->show();});
    connect(puts, &PutSW::SignalBackFunc, this, [=](){puts->hide(); this->show();});

    //入库信息
    PMsg->hide();
    connect(ui->BtnPutMsg,&QPushButton::clicked, this, [=](){this->hide(); PMsg->show();});
    connect(PMsg, &PutSWMsg::SignalBackFunc,this, [=](){this->show(); PMsg->hide();});

    //出库
    outs->hide();
    connect(ui->BtnOut,&QPushButton::clicked, this, [=](){this->hide(); outs->show();});
    connect(outs, &OutSW::signalBackFunc, this, [=](){this->show(); outs->hide();});

    //出库信息
    OMsg->hide();
    connect(ui->BtnOutMsg,&QPushButton::clicked, this, [=](){this->hide(); OMsg->show();});
    connect(OMsg, &OutSWMsg::signalBackFunc, this, [=](){this->show(); OMsg->hide();});

    //查询货物
    sstorage->hide();
    connect(ui->BtnSearch, &QPushButton::clicked, this, [=](){this->hide(); sstorage->show();});
    connect(sstorage,&SearchStorage::signalBackFunc,this,[=](){this->show(); sstorage->hide();});

    //修改信息
    mmsg->hide();
    connect(ui->BtnMdify,&QPushButton::clicked, this,[=](){this->hide(); mmsg->show();});
    connect(mmsg, &ModifyMSG::signalBackFunc, this, [=](){this->show(); mmsg->hide();});

    account->hide();
    connect(ui->BtnCreate, &QPushButton::clicked,this,[=](){this->hide();account->show();});

    ADel->hide();
    connect(ui->BtnADel, &QPushButton::clicked, this, [=](){this->hide(); ADel->show();});
    connect(ADel, &AccountDel::signalBackFunc, this, [=](){this->show(); ADel->hide();});

    AMdf->hide();
    connect(ui->BtnAMmodify,&QPushButton::clicked, this, [=](){this->hide(); AMdf->show();});
    connect(AMdf, &AccountModify::signalBackFunc, this, [=](){this->show(); AMdf->hide();});
}

StorageFunction::~StorageFunction()
{
    delete ui;
}
