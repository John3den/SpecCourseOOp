#include <string>
#include "Container.h"
#pragma once

class Object {
protected:
  static int objectCount;
public:
  virtual std::string toString() const {return ""; };
  Object() {}
  ~Object() {}
  static int GetCount() {
    return objectCount;
  }
};
 
int Object::objectCount = 0;

class Task : public Object {
public:
  bool executed = false;
  ~Task() {}
  virtual std::string toString() const
  {
    if (!executed)
      return  "this is a generic task that is yet to be executed!\n";
    else
      return  "this task has been executed!\n";
  }
  virtual void Execute() { };
protected:
  class RepeatedExecutionException : public std::exception {

  public:

    char* what()
    {
      return (char*)"This name is not an arithmetic operation!";
    }
  };
};

class TaskWithResult : public Task {
protected:
  int result = 0;
public:
  ~TaskWithResult() {}
  int GetResult() { return result; }
  virtual std::string toString() const
  {
    if (!executed)
      return  "this is a generic task with a result that is yet to be executed!\n";
    else
      return  "this task has been executed!\n";
  }
};

class Named : public Object {
public:

  std::string name = "unnamed";
};

class ClearContainer : public Task {
private:
  Container<Object>& _container;
public:
  ClearContainer(Container<Object>& container) : _container(container) 
  {
    objectCount++;
  }

  ~ClearContainer()
  {
    objectCount--;
  }

  void Execute() 
  { 
    if(executed) { throw RepeatedExecutionException(); }
    _container.Clear(); 
    executed = true;
  }
  
  virtual std::string toString() const
  {
    if(!executed)
      return  "this task will clear a container!\n";
    else
      return  "this task has cleared a container!\n";
  }
};

class CountObjects : public TaskWithResult, Named {
public:
  void Execute() 
  { 
    if (executed) { throw RepeatedExecutionException(); }
    result = Object::GetCount(); 
    executed = true;
  }

  CountObjects()
  {
    objectCount++;
  }

  ~CountObjects()
  {
    objectCount--;
  }

  virtual std::string toString() const
  {
    if (!executed)
      return  "this task will count created objects!\n";
    else
      return  "this task has counted "+ std::to_string(result) +" objects created!" + "\n";
  }
};

class AddTaskToContainer : public Task, Named {
private:
  Task& _task;
  Container<Task>& _container;
public:
  AddTaskToContainer(Container<Task>& container, Task& task) : 
                          _task(task), _container(container) { objectCount++; }

  ~AddTaskToContainer()
  {
    objectCount--;
  }
  void Execute() 
  {
    if (executed) { throw RepeatedExecutionException(); }
    _container.PushBack(_task);
    executed = true;
  }
  virtual std::string toString() const
  {
    if (!executed)
      return  "this task will add a task to a container!\n";
    else
      return  "this task had added a task to a container!\n";
  }
};

class CountObjectsInContainer : public TaskWithResult, Named {
private:
  Container<Object>& _container;
public:
  CountObjectsInContainer(Container<Object>& container) : _container(container) {objectCount++;}

  ~CountObjectsInContainer()
  {
    objectCount--;
  }

  void Execute() 
  {
    if (executed) { throw RepeatedExecutionException(); }
    result = _container.GetSize();
    executed = true;
  }
  virtual std::string toString() const 
  {
    if (!executed)
      return  "this task will count objects in a container!\n";
    else
      return  "this task has counted " + std::to_string(result) + " objects in a container!" + "\n";
  }
};

class CountTasksInContainer : public TaskWithResult, Named {
private:
  Container<Task*>& _container;
public:
  CountTasksInContainer(Container<Task*>& container) : _container(container) {objectCount++;}

  ~CountTasksInContainer()
  {
    objectCount--;
  }
  void Execute()
  {
    if (executed) { throw RepeatedExecutionException(); }
    result = _container.GetSize();
    executed = true;
  }

  virtual std::string toString() const
  {
    if (!executed)
      return  "this task will count tasks in a container!\n";
    else
      return  "this task has counted " + std::to_string(result) + " tasks in a container!" + "\n";
  }
};

class ArithmeticTask : public TaskWithResult, Named {

private:

  class NotAnOperationException : public std::exception {

  public:

    char* what()
    {
      return (char*)"This name is not an arithmetic operation!";
    }
  };

  enum class ArithmeticOperations { Add, Sub, Mul, Div};

  ArithmeticOperations StringToOperation(std::string s)
  {
    if(s == "Add") return ArithmeticOperations::Add;
    else if(s == "Sub") return ArithmeticOperations::Sub;
    else if(s == "Mul") return ArithmeticOperations::Mul;
    else if(s == "Div") return ArithmeticOperations::Div;
    else throw NotAnOperationException();
  }

  int _operand1;
  int _operand2;

public:

  ~ArithmeticTask()
  {
    objectCount--;
  }

  ArithmeticTask(std::string operation, int op1, int op2)
  {
    objectCount++;
    _operand1 = op1;
    _operand2 = op2;
    name = operation;
  }

  virtual void Execute()
  {
    if (executed) { throw RepeatedExecutionException(); }
    switch (StringToOperation(name))
    {
      case ArithmeticOperations::Add:
        result = _operand1 + _operand2;
      break;
      case ArithmeticOperations::Sub:
        result = _operand1 - _operand2;
      break;
      case ArithmeticOperations::Mul:
        result = _operand1 * _operand2;
      break;
      case ArithmeticOperations::Div:
        result = _operand1 / _operand2;
      break;
    }
    executed = true;
  }

  virtual std::string toString() const 
  {
    if (!executed)
      return "this task will perform a "+name+"operation on operands " + std::to_string(_operand1) + " and " + std::to_string(_operand2) + "\n";
    else
      return  "this task calculated the result of an " + name + " operation, and the result is " + std::to_string(result) + "\n";
  }
};

