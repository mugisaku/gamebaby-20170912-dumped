#include"rogie_task.hpp"
#include"rogie_taskmanager.hpp"
#include"gmbb.hpp"




Task::
Task(TaskCallback  cb, TaskManager*  mgr):
callback(cb),
manager(mgr),
worked_flag(false)
{
}




TaskManager*
Task::
get_manager() const
{
  return manager;
}


void
Task::
need_to_break_scanning()
{
    if(manager)
    {
      manager->need_to_break_scanning();
    }
}


void
Task::
push(ContextCallback  cb)
{
    if(cb)
    {
      context_stack.emplace(cb,manager,this);
    }
}


void
Task::
pop()
{
    if(context_stack.size())
    {
      context_stack.pop();
    }
}


bool
Task::
step()
{
    if(callback)
    {
      callback(*this);
    }


    if(context_stack.size())
    {
      auto&  ctx = context_stack.top();

        if(!ctx())
        {
          context_stack.pop();
        }
    }


  worked_flag = (callback || context_stack.size());

  return worked_flag;
}


bool
Task::
test_worked_flag() const
{
  return worked_flag;
}




