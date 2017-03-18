#ifndef ROGIE_TASKMANAGER_HPP_INCLUDED
#define ROGIE_TASKMANAGER_HPP_INCLUDED


#include"rogie_task.hpp"
#include<list>
#include<queue>




struct
TaskManager
{
  void*  owner;

  std::list<Task>  tasklist;

  std::queue<Context>  context_queue;

  bool  needed_to_sort;
  bool  needed_to_break_scanning;

public:
  TaskManager(std::initializer_list<TaskCallback>  tskcb={}, void*  owner_=nullptr);

  void*  get_owner() const;

  const std::queue<Context>&  get_context_queue() const;

  void  push(ContextCallback  cb);

  void  push_first(TaskCallback  cb);
  void  push_last( TaskCallback  cb);

  void  need_to_break_scanning();

  bool  scan();

  bool  operator()();

};




#endif




