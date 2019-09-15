#include "todomodel.h"

#include "todolist.h"

TodoModel::TodoModel(QObject *parent)
  : QAbstractListModel(parent)
  , mList(nullptr)
{
}

int TodoModel::rowCount(const QModelIndex &parent) const
{
  // For list models only the root node (an invalid parent) should return the list's size. For all
  // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
  if (parent.isValid())
    return 0;

  // FIXME: Implement me!
  return 100;
}

QVariant TodoModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  // FIXME: Implement me!
  switch (role)
  {
    case eDoneRole:
      return QVariant(false);

    case eDescriptionRole:
      return QVariant(QStringLiteral("Test description"));
  }

  return QVariant();
}

bool TodoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (data(index, role) != value) {
    // FIXME: Implement me!
    emit dataChanged(index, index, QVector<int>() << role);
    return true;
  }
  return false;
}

Qt::ItemFlags TodoModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::NoItemFlags;

  return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> TodoModel::roleNames() const
{
  QHash<int, QByteArray> names;

  names[eDoneRole]        = "done";
  names[eDescriptionRole] = "description";

  return names;
}

ToDoList *TodoModel::list() const
{
  return mList;
}

void TodoModel::setList(ToDoList *list)
{
  beginResetModel();

  if (mList)
  {
    mList->disconnect(this);
  }

  mList = list;

  if (mList)
  {
    connect(mList, &ToDoList::preItemAppended, this, [=]()
    {
      const int index = mList->items().size();
      beginInsertRows(QModelIndex(), index, index);
    });

    connect(mList, &ToDoList::postItemAppended, this, [=]()
    {
      endInsertRows();
    });

    connect(mList, &ToDoList::postItemRemoved, this, [=](int index)
    {
      beginRemoveRows(QModelIndex(), index, index);
    });
  }
}
