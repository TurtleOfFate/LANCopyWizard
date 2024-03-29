#include "LanSender.h"

LanSender::LanSender(QObject* parent) : QObject(parent)
{
	
}

void LanSender::PushIpToSend(QString ip_)
{
	ips.push_back(ip_);
}

void LanSender::PushFromPathToSend(QString pathFrom, int rowNumber)
{
	pairsOfPaths[rowNumber].first = pathFrom;
}

void LanSender::PushToPathToSend(QString pathTo, int rowNumber)
{
	pairsOfPaths[rowNumber].second = pathTo;
}
