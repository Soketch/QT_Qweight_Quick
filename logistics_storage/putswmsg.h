#ifndef PUTSWMSG_H
#define PUTSWMSG_H

#include <QWidget>

namespace Ui {
class PutSWMsg;
}

class PutSWMsg : public QWidget
{
    Q_OBJECT

public:
    explicit PutSWMsg(QWidget *parent = nullptr);

    void InitMSG();

    void ShowMSG();
    ~PutSWMsg();
signals:
    void SignalBackFunc();

public slots:
    void SlotBackFunc();
private:
    Ui::PutSWMsg *ui;
};

#endif // PUTSWMSG_H
