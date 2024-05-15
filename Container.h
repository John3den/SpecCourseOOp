#pragma once
#include <iterator>
#include <exception>


template<typename T>
class Container
{
public:

  class EmptyContainerPopException : public std::exception {

  public:

    char* what()
    {
      return "Pop function called from an empty container!";
    }
  };

  class Node
  {

  public:

    Node(const T data, Container<T>::Node* next = nullptr, Container<T>::Node* prev = nullptr);
    void SetNext(Node* next);
    void SetPrev(Node* next);
    typename Container<T>::Node* GetNext();
    typename Container<T>::Node* GetPrev();
    T GetData();
    void SetData(T data);

  private:

    T _data;
    Node* _next;
    Node* _prev;
  };

  Container();

  void PushFront(T data);
  void PushBack(T data);

  void PopFront();
  void PopBack();

  T Front();
  T Back();

  void Swap(Container& other);

  void Reverse();

  void Clear();

  bool IsEmpty()
  {
    return _size <= 0;
  }

  Node* GetRoot()
  {
    return _root;
  }
  Node* GetTail()
  {
    return _tail;
  }
  int GetSize()
  {
    return _size;
  }

  void SetRoot(Node* root)
  {
    _root = root;
  }
  void SetTail(Node* tail)
  {
    _tail = tail;
  }
  void SetSize(int size)
  {
    _size = size;
  }

  struct iterator
  {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Node;
    using pointer = Node*;
    using reference = Node&;

    explicit iterator(pointer ptr) : _ptr(ptr) {}
    T operator*() const { return _ptr->GetData(); }

    iterator& operator++() 
    { 
      _ptr = _ptr->GetNext();
      return *this; 
    }

    friend bool operator== (const iterator& a, const iterator& b) { return a._ptr == b._ptr; };
    friend bool operator!= (const iterator& a, const iterator& b) { return a._ptr != b._ptr; };

  private:
    pointer _ptr;
  };

private:

  Node* _root;
  Node* _tail;
  int _size;
};


