#include"ta.hpp"




RoutineState
visit_place()
{
    if(get_current_place())
    {
        if(!get_current_place()->react())
        {
          push_routine(select_main_command);
        }
    }


  return RoutineState::finished;
}




RoutineState
use_belongings()
{
    if(get_current_place())
    {
        if(!get_current_place()->react())
        {
          message.push(u"ここでは　つかえない　ようだ");
        }


      push_routine(select_main_command);
    }


  return RoutineState::finished;
}




RoutineState
leave_place()
{
    if(get_current_place())
    {
        if(!get_current_place()->react())
        {
          push_routine(visit_place);
        }


      change_current_place();
    }


  return RoutineState::finished;
}





