#ifndef PUTSW_H
#define PUTSW_H

#include <QWidget>

namespace Ui {
class PutSW;
}

class PutSW : public QWidget
{
    Q_OBJECT

public:
    explicit PutSW(QWidget *parent = nullptr);
    ~PutSW();

private slots:
    void on_BtnBack_clicked();
    void SaveFileMsg();

signals:
    void SignalBackFunc();
private:
    Ui::PutSW *ui;
};

#endif // PUTSW_H
