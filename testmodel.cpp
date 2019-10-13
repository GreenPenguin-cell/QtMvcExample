#include "testmodel.h"

TestModel::TestModel(QObject *parent):
    QAbstractListModel(parent)
{
    //    m_data.append("old");
    //    m_data.append("another old");
}

int TestModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_data.size();
}

QVariant TestModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    switch (role) {
    case CommandNameRole:
        return m_data.at(index.row()).name;// QVariant(index.row() < 2 ? "orange" : "skyblue");
    case CommandAliasRole:
        return m_data.at(index.row()).alias;
    case DopRole:
        return m_data.at(index.row()).dop;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> TestModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[CommandNameRole] = "CommandNameRole";
    roles[CommandAliasRole] = "CommandAliasRole";
    roles[DopRole] = "DopRole";

    return roles;
}

void TestModel::add(QString command, QString command_alias, QString dop)
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    Command com(command,command_alias, dop);
    m_data.append(com);
    endInsertRows();

    //m_data[0] = QString("Size: %1").arg(m_data.size());
    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

bool TestModel::removeRow(int row, const QModelIndex &parent)
{

    beginRemoveRows(parent, row,row);
    m_data.removeAt(row);
    endRemoveRows();
    return true;
}

void TestModel::change(int  index_row, QString command_value, QString alias_value)
{
    removeRow(index_row, QModelIndex());

    beginInsertRows(QModelIndex(), index_row, index_row);
    Command com(command_value,alias_value, "lol");
    m_data.insert(index_row, com);
    endInsertRows();
    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

bool TestModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }
    if(role == -1)
    {
        m_data[index.row()].name = value.toString();
    }
    else
    {
        switch (role) {
        case CommandNameRole:
            m_data[index.row()].name = value.toString();
            break;
        case CommandAliasRole:
            m_data[index.row()].alias = value.toString();
            break;
        default:
            return false;
        }
    }

    emit dataChanged(index, index, QVector<int>() << role);

    return true;
}

Qt::ItemFlags TestModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}
