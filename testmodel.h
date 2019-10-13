#ifndef TESTMODEL_H
#define TESTMODEL_H

#include <QObject>
#include "QAbstractItemModel"
#include "QMap"

class TestModel : public QAbstractListModel
{
    Q_OBJECT

public:
    struct Command
    {
        Command(QString name, QString alias) {
            this->alias = alias;
            this->name = name;
        }
        QString name;
        QString alias;
    };

    enum Roles {
        CommandNameRole = Qt::UserRole + 1,
        CommandAliasRole
    };

    TestModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    Q_INVOKABLE void add(QString command, QString alias);
    Q_INVOKABLE virtual bool removeRow(int row, const QModelIndex &parent);
    Q_INVOKABLE void change(int  index_row, QString command_value, QString alias_value);


private:
    QList<Command> m_data;

};

#endif // TESTMODEL_H
