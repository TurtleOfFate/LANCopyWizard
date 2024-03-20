#include "IPAddressModel.h"


Q_INVOKABLE int IPAddressModel::rowCount(const QModelIndex& parent) const
{
    return addresses_.count();
}

Q_INVOKABLE QVariant IPAddressModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) 
        return QVariant();
    if (index.row() < 0 || index.row() > addresses_.count())
        return QVariant();

    const IPAddress& ip = addresses_[index.row()];
    if (role == Qt::DisplayRole)
        return ip.getAddress();

    return QVariant();
}

Q_INVOKABLE QModelIndex IPAddressModel::index(int row, int column, const QModelIndex& parent) const
{
    return createIndex(row, column, nullptr);
}

Q_INVOKABLE QModelIndex IPAddressModel::parent(const QModelIndex& child) const
{
    return Q_INVOKABLE QModelIndex();
}

Q_INVOKABLE int IPAddressModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}
