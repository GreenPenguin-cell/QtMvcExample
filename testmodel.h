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
        Command(QString name, QString alias, QString dop = "none") {
            this->alias = alias;
            this->name = name;
            this->dop = dop;
        }
        QString name;
        QString alias;
        QString dop;
    };

    enum Roles {
        CommandNameRole = Qt::UserRole + 1,
        CommandAliasRole = Qt::UserRole + 2,
        DopRole
    };

    TestModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    Q_INVOKABLE void add(QString command, QString command_alias, QString dop = "lal");
    Q_INVOKABLE virtual bool removeRow(int row, const QModelIndex &parent);
    Q_INVOKABLE void change(int  index_row, QString command_value, QString alias_value);


private:
    QList<Command> m_data;

};

#endif // TESTMODEL_H
