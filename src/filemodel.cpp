#include "filemodel.h"

FileModel::FileModel(QObject *parent) : QAbstractTableModel(parent)
{
}

int FileModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return files.count();
}

int FileModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return LAST;
}

QVariant FileModel::data(const QModelIndex &index, int role) const
{
// if (role == Qt::BackgroundRole) {
// if (index.row() % 2)
// return QBrush(QColor(242, 242, 242));
// return QBrush(QColor(Qt::white));
// }

    error_code ec;

    if (!index.isValid()
        || files.count() <= index.row()
        || (role != Qt::DisplayRole && role != Qt::EditRole))
        return QVariant();

    path requiredPath = files[index.row()];

    switch (index.column()) {
    case Column::FILE_NAME:
    {
        if (is_directory(requiredPath, ec)
            && ec.value() == errc::success)
            return QString::fromStdWString(requiredPath.filename().wstring());
        return QString::fromStdWString(
            requiredPath.has_extension()
            ? requiredPath.stem().wstring()
            : requiredPath.filename().wstring()
            );
    }
    case Column::FILE_TYPE:
    {
        if (is_directory(requiredPath, ec)
            && ec.value() == errc::success)
            return "";
        return QString::fromStdWString(requiredPath.extension().wstring());
    }
    case Column::FILE_SIZE:
    {
        if (IsDirectoryJunction(requiredPath.wstring().c_str())
            || is_symlink(requiredPath))
            return "<ССЫЛКА>";

        if (is_directory(requiredPath)) return "<ПАПКА>";

        uintmax_t fileSize = file_size(requiredPath, ec);
        if (ec.value() == errc::success)
            return QString::number(fileSize);

        return "";
    }
    case Column::FILE_DATE:
    {
        time_t time = last_write_time(requiredPath, ec);
        if (ec.value() == errc::success) {
            return QString::fromStdWString(
                boost::posix_time::to_simple_wstring(
                    boost::posix_time::from_time_t(
                        time)));
        }
        return "";
    }
    }

    return QVariant();
}

QVariant FileModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation == Qt::Vertical) return section;

    switch (section) {
    case Column::FILE_NAME:
        return "Имя";
    case Column::FILE_TYPE:
        return "Тип";
    case Column::FILE_SIZE:
        return "Размер";
    case Column::FILE_DATE:
        return "Дата";
    }

    return QVariant();
}

void FileModel::reserModel(Files &newFiles)
{
    beginResetModel();
    files.clear();
    files = newFiles;
    endResetModel();
}
