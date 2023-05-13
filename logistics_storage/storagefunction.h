#ifndef STORAGEFUNCTION_H
#define STORAGEFUNCTION_H

#include <QWidget>
#include<putsw.h>
#include<putswmsg.h>
#include<outsw.h>
#include<outswmsg.h>
#include<modifymsg.h>
#include<searchstorage.h>
#include<createwidget.h>
#include<accountdel.h>
#include<accountmodify.h>
namespace Ui {
class StorageFunction;
}

class StorageFunction : public QWidget
{
    Q_OBJECT

public:
    explicit StorageFunction(QWidget *parent = nullptr);
    ~StorageFunction();

private:
    Ui::StorageFunction *ui;
    PutSW* puts = new PutSW;
    PutSWMsg * PMsg = new PutSWMsg;
    OutSW* outs = new OutSW;
    OutSWMsg * OMsg = new OutSWMsg;
    ModifyMSG * mmsg = new ModifyMSG;
    SearchStorage* sstorage = new SearchStorage;
    CreateWidget * account = new CreateWidget;
    AccountDel * ADel = new AccountDel;
    AccountModify * AMdf= new AccountModify;
};

#endif // STORAGEFUNCTION_H
