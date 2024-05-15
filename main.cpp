#include "Container.h"
#include "Container.cpp"
#include <iostream>
#include "Object.h"
using namespace std;

class TaskReport : Object
{
private:
  std::string _text;
public:
  TaskReport() {
    _text = "";
  }
  TaskReport(std::string text) {
    _text = text;
  }
  void Print(){
    std::cout<< _text;
  }
};

int main() {

  Container<Task*> tasks;

  ArithmeticTask* arithmetic1 = new ArithmeticTask("Add", 1, 3);
  ArithmeticTask* arithmetic2 = new ArithmeticTask("Sub", 1000, 7);
  ArithmeticTask* arithmetic3 = new ArithmeticTask("Sub", 993, 7);
  CountObjects* count1 = new CountObjects();
  ArithmeticTask* arithmetic4 = new ArithmeticTask("Mul", 190, 13);
  ArithmeticTask* arithmetic5 = new ArithmeticTask("Div", 777, 7);
  ArithmeticTask* arithmetic6 = new ArithmeticTask("Add", 103,81);
  ArithmeticTask* arithmetic7 = new ArithmeticTask("Sub", 1111, 999);
  ArithmeticTask* arithmetic8 = new ArithmeticTask("Mul", 135, 32);
  CountTasksInContainer* countTasks1 = new CountTasksInContainer(tasks);
  ArithmeticTask* arithmetic9 = new ArithmeticTask("Div", 121, 11);
  ArithmeticTask* arithmetic10 = new ArithmeticTask("Add", 444, 22);

  tasks.PushBack(arithmetic1);
  tasks.PushBack(arithmetic2);
  tasks.PushBack(arithmetic3);
  tasks.PushBack(count1);
  tasks.PushBack(arithmetic4);
  tasks.PushBack(arithmetic5);
  tasks.PushBack(arithmetic6);
  tasks.PushBack(arithmetic7);
  tasks.PushBack(arithmetic8);
  tasks.PushBack(countTasks1);
  tasks.PushBack(arithmetic9);  
  tasks.PushBack(arithmetic10);


  Container<TaskReport> reports;

  std::cout<< "total object count is "<< Object::GetCount()<<"\n";

Container<Task*>::iterator taskIter(tasks.GetRoot());
  for(;0 < tasks.GetSize();) {
    Task* t = tasks.Back();
    tasks.PopBack();
    (*t).Execute();
    TaskReport report((*t).toString());
    reports.PushBack(report);
    
  }

  Container<TaskReport>::iterator repIter(reports.GetRoot());
  for (int i = 0; i<reports.GetSize(); ++repIter)
  {
    i++;
    TaskReport r = *repIter;
    r.Print();
  }
  
   tasks.Clear();
   reports.Clear();

  std::cout<<"Deleting TASKS..."<< "\n";

  delete arithmetic1;
  delete arithmetic2;
  delete arithmetic3;
  delete arithmetic4;
  delete arithmetic5;
  delete arithmetic6;
  delete arithmetic7;
  delete arithmetic8;
  delete arithmetic9;
  delete arithmetic10;
  delete count1;
  delete countTasks1;
  
  std::cout << "total object count is " << Object::GetCount() << "\n";
  return 0;
}