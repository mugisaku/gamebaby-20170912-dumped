#ifndef ROGIE_CONTEXT_HPP_INCLUDED
#define ROGIE_CONTEXT_HPP_INCLUDED


#include<cstdint>




struct Context;
struct Task;
struct TaskManager;


using ContextCallback = void(*)(Context&  ctx);


struct
Context
{
  ContextCallback  callback;

  TaskManager*  taskmanager;
  Task*         task       ;

  int  memory[8];

  Context(ContextCallback  cb, TaskManager*  tskmgr=nullptr, Task*  tsk=nullptr):
  callback(cb), taskmanager(tskmgr), task(tsk), memory{0}{}


  bool  operator()()
  {
      if(callback)
      {
        callback(*this);
      }


    return callback;
  }

};


#endif




