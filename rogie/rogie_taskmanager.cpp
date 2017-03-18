#include"rogie_taskmanager.hpp"
#include"gmbb.hpp"




TaskManager::
TaskManager(std::initializer_list<TaskCallback>  tskcb, void*  owner_):
owner(owner_)
{
    for(auto  cb: tskcb)
    {
      push_last(cb);
    }
}




void*
TaskManager::
get_owner() const
{
  return owner;
}


const std::queue<Context>&
TaskManager::
get_context_queue() const
{
  return context_queue;
}


void
TaskManager::
push(ContextCallback  cb)
{
    if(cb)
    {
      context_queue.emplace(cb,this,nullptr);
    }
}


void  TaskManager::push_first(TaskCallback  cb){if(cb){tasklist.emplace_front(cb,this);};}
void  TaskManager::push_last( TaskCallback  cb){if(cb){tasklist.emplace_back( cb,this);};}


void
TaskManager::
need_to_break_scanning()
{
  needed_to_break_scanning = true;
}


bool
TaskManager::
scan()
{
  bool  flag = tasklist.size();

  needed_to_break_scanning = false;

  auto   it = tasklist.begin();
  auto  end = tasklist.end();

    while(it != end)
    {
        if(!it->step())
        {
          it = tasklist.erase(it);
        }

      else
        {
          ++it;
        }


        if(needed_to_break_scanning)
        {
          break;
        }
    }


  return flag;
}


bool
TaskManager::
operator()()
{
  bool  flag = false;

    if(context_queue.size())
    {
      auto&  ctx = context_queue.front();

        if(!ctx())
        {
          context_queue.pop();
        }


      flag = true;
    }


  flag |= scan();

  return flag;
}




