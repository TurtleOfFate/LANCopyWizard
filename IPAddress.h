#pragma once
#include <string>
#include <qstring.h>

class IPAddress
{
public:
    IPAddress();
    IPAddress(const QString& address);
    inline QString getAddress() const { return address_; }
    //void validate();
private:
    QString address_;
};

