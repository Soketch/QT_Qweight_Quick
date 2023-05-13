#ifndef ACCOUNTMODIFY_H
#define ACCOUNTMODIFY_H

#include <QWidget>

namespace Ui {
class AccountModify;
}

class AccountModify : public QWidget
{
    Q_OBJECT

public:
    explicit AccountModify(QWidget *parent = nullptr);
    void tableInit();
    void showMSG();
    ~AccountModify();
public slots:
    void slotBackFunc();
    void SlotAM();
signals:
    void signalBackFunc();
private:
    Ui::AccountModify *ui;
};

#endif // ACCOUNTMODIFY_H
