#include "IPAddress.h"

IPAddress::IPAddress()
{
	address_ = "127.0.0.1";
}

IPAddress::IPAddress(const QString& address)
{
	address_ = address;
}
