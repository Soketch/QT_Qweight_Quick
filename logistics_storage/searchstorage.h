#ifndef SEARCHSTORAGE_H
#define SEARCHSTORAGE_H

#include <QWidget>

namespace Ui {
class SearchStorage;
}

class SearchStorage : public QWidget
{
    Q_OBJECT

public:
    explicit SearchStorage(QWidget *parent = nullptr);
    void tableInit();
    ~SearchStorage();
public slots:
    void SlotBackFunc();
    void showMsg();
signals:
    void signalBackFunc();
private:
    Ui::SearchStorage *ui;
};

#endif // SEARCHSTORAGE_H
