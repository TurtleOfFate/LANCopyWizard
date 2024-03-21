#pragma once
#include <qabstractitemmodel.h>
#include "IPAddress.h"

class IPAddressModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	IPAddressModel(QObject* parent = 0) 
	{
		addresses_.append(IPAddress());
		addresses_.append(IPAddress("142194"));
	};

	virtual Q_INVOKABLE int rowCount(const QModelIndex& parent) const override;
	virtual Q_INVOKABLE QVariant data(const QModelIndex& index, int role) const override;
	virtual Q_INVOKABLE QModelIndex index(int row, int column, const QModelIndex& parent) const override;
	virtual Q_INVOKABLE QModelIndex parent(const QModelIndex& child) const override;
	virtual Q_INVOKABLE int columnCount(const QModelIndex& parent) const override;
private:
	QList<IPAddress> addresses_;

	
};

