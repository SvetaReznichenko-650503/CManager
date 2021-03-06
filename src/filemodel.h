#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QDebug>
#include <QRegularExpression>

#include <boost/filesystem.hpp>
#include <boost/date_time.hpp>

#include "junctionpoint.h"

using namespace boost::filesystem;
using namespace boost::system;
using namespace neosmart;

typedef QList<path> Files;

enum Column {
    FILE_NAME = 0,
    FILE_TYPE,
    FILE_SIZE,
    FILE_DATE,
    LAST
};

class FileModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit FileModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void resetModel(Files &newFiles);

    int contentCount();
    path getContent(int index);
    QString formatSizeByThousands(QString original) const;

private:

    Files files;
};

#endif // FILEMODEL_H
