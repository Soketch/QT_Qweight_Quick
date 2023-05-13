#ifndef OUTSW_H
#define OUTSW_H

#include <QWidget>

namespace Ui {
class OutSW;
}

class OutSW : public QWidget
{
    Q_OBJECT

public:
    explicit OutSW(QWidget *parent = nullptr);
    void Init();

    void showAllMsg();

    ~OutSW();
public slots:
    void SlotBackFunc();
    void OutOKMsg();
    void getItem(const QModelIndex &index);
signals:
    void signalBackFunc();
private:
    Ui::OutSW *ui;
    int m_count;
    int temp;
};

#endif // OUTSW_H
