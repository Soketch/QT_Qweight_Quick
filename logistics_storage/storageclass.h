#ifndef STORAGECLASS_H
#define STORAGECLASS_H

#include<QString>
#include<QFile>
#include<QList>

class StorageClass
{
public:
    StorageClass();

    void setName(const QString &value);
    QString getName() const;

    QString getSite() const;
    void setSite(const QString &value);

    int getNum() const;
    void setNum(int value);

    QString getDateTime() const;
    void setDateTime(const QString &value);

public:
    //四个属性  名称  位置  数量   时间
    QString name;
    QString Site;
    int num;
    QString dateTime;

};

#endif // STORAGECLASS_H
