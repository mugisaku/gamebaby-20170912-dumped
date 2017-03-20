#ifndef ROGIE_TASK_HPP_INCLUDED
#define ROGIE_TASK_HPP_INCLUDED


#include<cstdint>


struct Task;

using TaskCallback = void(*)(Task&  tsk, void*  caller);


struct
Task
{
  TaskCallback  callback;

  int  memory[8];

  Task(TaskCallback  cb=nullptr):
  callback(cb), memory{0}{}

};




#endif




