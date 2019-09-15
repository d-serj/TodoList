#ifndef TODOLIST_H
#define TODOLIST_H

#include <QObject>
#include <QVector>

struct ToDoItem
{
  bool is_done;
  QString descriptioin;
};

class ToDoList : public QObject
{
  Q_OBJECT

public:
  explicit ToDoList(QObject *parent = nullptr);

  QVector<ToDoItem> items() const;

  bool setItemAt(int index, const ToDoItem &item);

signals:
  void preItemAppended(void);
  void postItemAppended(void);

  void preItemRemoved(int index);
  void postItemRemoved(void);

public slots:
  void appendItem(void);
  void removeCompletedItems(void);

private:
  QVector<ToDoItem> mItems;
};

#endif // TODOLIST_H
