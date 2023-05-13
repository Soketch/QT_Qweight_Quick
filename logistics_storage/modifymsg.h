#ifndef MODIFYMSG_H
#define MODIFYMSG_H

#include <QWidget>

namespace Ui {
class ModifyMSG;
}

class ModifyMSG : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyMSG(QWidget *parent = nullptr);
    void Init();

    void showAllMsg();

    ~ModifyMSG();
public slots:
    void SlotBackFunc();

    void SlotBtnOKMsg();

    void getItem(const QModelIndex &index);
signals:
    void signalBackFunc();
private:
    Ui::ModifyMSG *ui;
    int m_Count;
};

#endif // MODIFYMSG_H
