#include "Container.h"

template<typename T>
Container<T>::Container()
{
  _size = 0;
  _root = nullptr;
  _tail = nullptr;
}


template<typename T>
void Container<T>::PushFront(T data)
{
  if (_size == 0)
  {
    Container<T>::Node* n = new Container<T>::Node(data);
    _root = n;
    _tail = n;
  }
  else
  {
    Container<T>::Node* newRoot = new Container<T>::Node(data, _root, nullptr);
    _root->SetPrev(newRoot);
    _root = newRoot;
  }
  _size++;
}

template<typename T>
void Container<T>::PushBack(T data)
{
  if (_size == 0)
  {
    Container<T>::Node* n = new Container<T>::Node(data);
    _root = n;
    _tail = n;
  }
  else
  {
    Container<T>::Node* newTail = new Container<T>::Node(data, nullptr, _tail);
    _tail->SetNext(newTail);
    _tail = newTail;
  }
  _size++;
}

template<typename T>
void Container<T>::PopFront()
{
  switch(_size)
  { 
  case 0:
    throw EmptyContainerPopException();
  break; 
  case 1:
    delete _root;
    _root = nullptr;
    _tail = nullptr;
  break;
  default:
    Container<T>::Node* oldRoot = _root;
    _root = _root->GetNext();
    _root->SetPrev(nullptr);
    delete oldRoot;
  break;
  }
  _size--;
}

template<typename T>
void Container<T>::PopBack()
{
  switch (_size)
  {
  case 0:
    throw EmptyContainerPopException();
    break;
  case 1:
    delete _root;
    _root = nullptr;
    _tail = nullptr;
    break;
  default:
    Container<T>::Node* oldTail = _tail;
    _tail = _tail->GetPrev();
    _tail->SetNext(nullptr);
    delete oldTail;
    break;
  }
  _size--;
}

template<typename T>
T Container<T>::Front()
{
  return _root->GetData();
}
template<typename T>

T Container<T>::Back()
{
  return _tail->GetData();
}

template<typename T>
void Container<T>::Swap(Container& other)
{
  Node* bRoot = _root;
  Node* bTail = _tail;
  int bSize = _size;

  _root = other.GetRoot();
  _tail = other.GetTail();
  _size = other.GetSize();

  other.SetRoot(bRoot);
  other.SetTail(bTail);
  other.SetSize(bSize);
}

template<typename T>
void Container<T>::Reverse()
{ 
  int ln = 0;
  int rn = _size-1;

  Node* l = _root;
  Node* r = _tail;

  while (ln < rn)
  {
    T dataBuffer = l->GetData();
    l->SetData(r->GetData());
    r->SetData(dataBuffer);
    ln++; rn++;
    l = l->GetNext();
    r = r->GetPrev();
  }
}

template<typename T>
void Container<T>::Clear()
{
  while(_size > 0) PopBack();
}

template<typename T>
Container<T>::Node::Node(T data, Container<T>::Node* next, Container<T>::Node* prev)
{
  _data = data;
  _next = next;
  _prev = prev;
}

template<typename T>
void Container<T>::Node::SetNext(Container<T>::Node* next)
{
  _next = next;
}

template<typename T>
void Container<T>::Node::SetPrev(Container<T>::Node* prev)
{
  _prev = prev;
}

template<typename T>
typename Container<T>::Node* Container<T>::Node::GetNext()
{
  return _next;
}

template<typename T>
typename Container<T>::Node* Container<T>::Node::GetPrev()
{
  return _prev;
}

template<typename T>
T Container<T>::Node::GetData()
{
  return _data;
}

template<typename T>
void Container<T>::Node::SetData(T data)
{
  _data = data;
}

