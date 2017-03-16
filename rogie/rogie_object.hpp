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
Object
{
  std::queue<Callback>  action_queue;

  std::stack<Context>  work_stack;

  std::list<Context>  task_list;

  bool  needed_to_break_scanning;

  void*  userdata;

public:
  Object(Callback  first_cb=default_first_callback, void*  userdata_=nullptr);

  void*  get_userdata() const;
  void  set_userdata(void*  data);

  void  push_task_to_first(Callback  cb);
  void  push_task_to_last(Callback  cb);
  void  push_action(Callback  cb);

  void  push_work(Callback  cb);
  void  pop_work();

  void  step();

  void  scan_task_list();

  void  need_to_break_scanning();


  static void  default_first_callback(Context&  ctx);

};




#endif




