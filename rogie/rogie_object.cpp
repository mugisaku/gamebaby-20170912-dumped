#include"rogie_object.hpp"
#include"gmbb.hpp"




Object::
Object(Callback  first_cb, void*  userdata_):
userdata(userdata_)
{
  push_work(first_cb);
}




void*  Object::get_userdata() const{return userdata;}
void   Object::set_userdata(void*  data){userdata = data;}




void
Object::
push_task_to_first(Callback  cb)
{
    if(cb)
    {
      task_list.emplace_front(cb,this);
    }
}


void
Object::
push_task_to_last(Callback  cb)
{
    if(cb)
    {
      task_list.emplace_back(cb,this);
    }
}


void
Object::
push_action(Callback  cb)
{
    if(cb)
    {
      action_queue.emplace(cb);
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
}


void
Object::
scan_task_list()
{
  needed_to_break_scanning = false;

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


        if(needed_to_break_scanning)
        {
          break;
        }
    }
}


void
Object::
need_to_break_scanning()
{
  needed_to_break_scanning = true;
}


void
Object::
default_first_callback(Context&  ctx)
{
  auto&  obj = *ctx.caller;

    if(obj.work_stack.size() == 1)
    {
        if(obj.action_queue.size())
        {
          auto&  t = obj.action_queue.front();

          obj.work_stack.emplace(t,&obj);

          obj.action_queue.pop();
        }

      else
        {
          obj.scan_task_list();
        }
    }
}




