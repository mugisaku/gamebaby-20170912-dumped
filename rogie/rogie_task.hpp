#ifndef ROGIE_TASK_HPP_INCLUDED
#define ROGIE_TASK_HPP_INCLUDED


#include"rogie_context.hpp"
#include<stack>




struct TaskManager;


using TaskCallback = void(*)(Task&  tsk);


struct
Task
{
  TaskManager*  manager;

  TaskCallback  callback;

  std::stack<Context>  context_stack;

  bool  worked_flag;

public:
  Task(TaskCallback  cb, TaskManager*  mgr=nullptr);

  TaskManager*  get_manager() const;

  void  need_to_break_scanning();

  void  push(ContextCallback  cb);
  void  pop();

  bool  step();

  bool  test_worked_flag() const;

};




#endif




