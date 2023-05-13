#include "storageclass.h"

StorageClass::StorageClass()
{

}

QString StorageClass::getDateTime() const
{
    return dateTime;
}

void StorageClass::setDateTime(const QString &value)
{
    dateTime = value;
}

int StorageClass::getNum() const
{
    return num;
}

void StorageClass::setNum(int value)
{
    num = value;
}

QString StorageClass::getSite() const
{
    return Site;
}

void StorageClass::setSite(const QString &value)
{
    Site = value;
}

QString StorageClass::getName() const
{
    return name;
}

void StorageClass::setName(const QString &value)
{
    name = value;
}
