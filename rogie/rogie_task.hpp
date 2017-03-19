#ifndef ROGIE_TASK_HPP_INCLUDED
#define ROGIE_TASK_HPP_INCLUDED


#include<cstdint>


struct Task;

using Callback = void(*)(Task&  tsk, void*  caller);


struct
Task
{
  Callback  callback;

  int  memory[8];

};




#endif




