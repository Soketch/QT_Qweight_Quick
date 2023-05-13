#ifndef ACCOUNTDEL_H
#define ACCOUNTDEL_H

#include <QWidget>

namespace Ui {
class AccountDel;
}

class AccountDel : public QWidget
{
    Q_OBJECT

public:
    explicit AccountDel(QWidget *parent = nullptr);
    void tableInit();
    void showMSG();
    ~AccountDel();
public slots:
    void slotBackFunc();
    void slotBtnOK();
signals:
    void signalBackFunc();
private:
    Ui::AccountDel *ui;
};

#endif // ACCOUNTDEL_H
