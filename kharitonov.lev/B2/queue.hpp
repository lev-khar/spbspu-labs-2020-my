#ifndef QUEUE_WITH_PRIORITY_HPP
#define QUEUE_WITH_PRIORITY_HPP

#include <list>
#include <stdexcept>

template<typename T>
class QueueWithPriority
{
public:
  enum ElementPriority
  {
    LOW,
    NORMAL,
    HIGH
  };
  void putElementToQueue(const T& element, ElementPriority priority);
  T getElementFromQueue();
  void removeFirst();
  void accelerate();
  bool isEmpty() const;
private:
  std::list<T> priorityLists[HIGH + 1];
};

template<typename T>
void QueueWithPriority<T>::putElementToQueue(const T& element, ElementPriority priority)
{
  if ((priority < 0) || (priority >= sizeof(priorityLists) / sizeof(priorityLists[0])))
  {
    throw std::invalid_argument("Wrong priority parameter");
  }

  priorityLists[priority].push_back(element);
}

template<typename T>
T QueueWithPriority<T>::getElementFromQueue()
{
  for (size_t i = (sizeof(priorityLists) / sizeof(priorityLists[0]) - 1); i >= 0; i--)
  {
    if (!priorityLists[i].empty())
    {
      return priorityLists[i].front();
    }
  }
  throw std::runtime_error("The queue is empty");
}

template<typename T>
void QueueWithPriority<T>::removeFirst()
{
  for (size_t i = (sizeof(priorityLists) / sizeof(priorityLists[0]) - 1); i >= 0; i--)
  {
    if (!priorityLists[i].empty())
    {
      priorityLists[i].pop_front();
      return;
    }
  }
  throw std::runtime_error("The queue is empty");
}

template<typename T>
void QueueWithPriority<T>::accelerate()
{
  priorityLists[HIGH].splice(priorityLists[HIGH].end(), priorityLists[LOW]);
}

template<typename T>
bool QueueWithPriority<T>::isEmpty() const
{
  for (size_t i = 0; i < sizeof(priorityLists) / sizeof(priorityLists[0]); i++)
  {
    if (!priorityLists[i].empty())
    {
      return false;
    }
  }
  return true;
}

#endif
