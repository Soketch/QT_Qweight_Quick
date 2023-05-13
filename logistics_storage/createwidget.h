#ifndef CREATEWIDGET_H
#define CREATEWIDGET_H

#include <QWidget>

namespace Ui {
class CreateWidget;
}

class CreateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CreateWidget(QWidget *parent = nullptr);
    ~CreateWidget();
public slots:
    void SlotSave();
private:
    Ui::CreateWidget *ui;
};

#endif // CREATEWIDGET_H
