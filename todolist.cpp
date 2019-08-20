#include "todolist.h"

ToDoList::ToDoList(QObject *parent) : QObject(parent)
{

}

QVector<ToDoItem> ToDoList::items() const
{
  return mItems;
}

bool ToDoList::setItemAt(int index, const ToDoItem &item)
{
  if ((index < 0) || (index > mItems.size()))
  {
    // TODO: implement me
  }
}
