#include"rogie_object.hpp"




Object::
Object(uint32_t  flags_):
flags(flags_),
action_currency(0),
userdata(nullptr)
{
}




void*  Object::get_userdata() const{return userdata;}
void   Object::set_userdata(void*  data){userdata = data;}


void    Object::set_flag(uint32_t  v){flags |=  v;}
void  Object::unset_flag(uint32_t  v){flags &= ~v;}
bool   Object::test_flag(uint32_t  v) const{return(flags&v);}




void
Object::
push_task_front(Callback  cb)
{
    if(cb)
    {
      task_list.emplace_front(cb,this);
    }
}


void
Object::
push_task_back(Callback  cb)
{
    if(cb)
    {
      task_list.emplace_back(cb,this);
    }
}


void
Object::
push_action(Callback  cb, int  consum)
{
    if(cb)
    {
      action_queue.emplace(Action{cb,consum});
    }
}


void
Object::
push_work(Callback  cb)
{
    if(cb)
    {
      work_stack.emplace(cb,this);
    }
}


void
Object::
pop_work()
{
    if(work_stack.size())
    {
      work_stack.pop();
    }
}


void
Object::
step()
{
    if(work_stack.size())
    {
      auto&  bk = work_stack.top();

      bk.callback(bk);

        if(!bk.callback)
        {
          work_stack.pop();
        }
    }

  else
    if(action_queue.size())
    {
      auto&  t = action_queue.front();

        if(!t.consumption || (action_currency >= 0))
        {
          action_currency -= t.consumption;

          work_stack.emplace(t.callback,this);

          action_queue.pop();
        }
    }

  else
    if(flags&voluntary_flag)
    {
      set_flag(taskseeking_flag);

      auto   it = task_list.begin();
      auto  end = task_list.end();

        while(it != end)
        {
          it->callback(*it);

            if(!it->callback)
            {
              it = task_list.erase(it);
            }

          else
            {
              ++it;
            }


            if(!test_flag(taskseeking_flag))
            {
              break;
            }
        }
    }
}




