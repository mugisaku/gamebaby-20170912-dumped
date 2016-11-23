#include"ta.hpp"




namespace{


int
phase;


int
direct;


std::queue<Routine>
q;


Place*  current_place;
Place*     next_place;


gmbb::Object*
current_object;


bool
message_flag;


}



void
change_current_place()
{
  current_place = next_place          ;
                  next_place = nullptr;
}


Place*
get_current_place()
{
  return current_place;
}


void
set_next_place(Place*  plc)
{
  next_place = plc;
}




gmbb::Object*  get_current_object(){return current_object;}
void   change_current_object(gmbb::Object*  obj){current_object = obj;}


void       set_this_place_flags(uint32_t  v){current_place->flags.set(v);}
void     unset_this_place_flags(uint32_t  v){current_place->flags.unset(v);}
uint32_t  test_this_place_flags(uint32_t  v){return current_place->flags.test(v);}


int   get_direct(){return direct;}
void  change_direct(int  v){direct = v;}


int
get_routine_phase()
{
  return phase;
}


void
change_routine_phase(int  v)
{
  phase = v;
}




void
push_routine(Routine  r)
{
  q.emplace(r);
}


Routine
get_current_routine()
{
  return q.size()? q.front():nullptr;
}




bool
step()
{
    if(message_flag)
    {
        if(message.is_finished())
        {
          message_flag = false;
        }


      return true;
    }


    if(q.size())
    {
        if(get_current_routine()() == RoutineState::finished)
        {
          change_routine_phase(0);

          q.pop();
        }
    }


    if(!message.is_finished())
    {
      table_window.change_content(&message);

      change_current_object(&message);

      message_flag = true;

      return true;
    }


  return q.size();
}


RoutineState
newgame()
{
   table_window.set_state(gmbb::WindowState::full_opened);
  pillar_window.set_state(gmbb::WindowState::full_opened);

  set_next_place(&beginning_room::place);

  message.clear();

  message.push({u"コマンドせんたくがた",
                u"テキストアドベンチャーの はじまり"});


  change_current_place();

  change_main_command(0);
  change_action_command(invalid_command);
  change_direct(0);

  change_routine_phase(0);

  push_routine(visit_place);


  return RoutineState::finished;
}




