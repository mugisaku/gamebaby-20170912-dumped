#ifndef ROGIE_OBJECT_HPP_INCLUDED
#define ROGIE_OBJECT_HPP_INCLUDED


#include<cstdint>
#include<list>
#include<queue>
#include<stack>




struct Context;
struct Object;


using Callback = void(*)(Context&  ctx);


struct
Context
{
  Callback  callback;

  Object*  caller;

  int  memory[8];

  Context(Callback  cb, Object*  caller_=nullptr):
  callback(cb), caller(caller_), memory{0}{}

};




struct
Action
{
  Callback  callback;

  int  consumption;

};


struct
Object
{
  static constexpr uint32_t  voluntary_flag   = 1;
  static constexpr uint32_t  taskseeking_flag = 2;


  uint32_t  flags;

  int  action_currency;

  std::queue<Action>  action_queue;

  std::stack<Context>  work_stack;

  std::list<Context>  task_list;

  void*  userdata;

public:
  Object(uint32_t  flags_);

  void*  get_userdata() const;
  void  set_userdata(void*  data);

  void  push_task_front(Callback  cb);
  void  push_task_back(Callback  cb);
  void  push_action(Callback  cb, int  consum);
  void  push_work(Callback  cb);
  void  pop_work();
  void  step();

  void    set_flag(uint32_t  v);
  void  unset_flag(uint32_t  v);
  bool   test_flag(uint32_t  v) const;

};




#endif




