#ifndef OUTSWMSG_H
#define OUTSWMSG_H

#include <QWidget>

namespace Ui {
class OutSWMsg;
}

class OutSWMsg : public QWidget
{
    Q_OBJECT

public:
    explicit OutSWMsg(QWidget *parent = nullptr);
    void Init();

    void showAllMsg();

    ~OutSWMsg();
public slots:
    void slotBackFunc();
signals:
    void signalBackFunc();
private:
    Ui::OutSWMsg *ui;
};

#endif // OUTSWMSG_H
