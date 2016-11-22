#include"game.hpp"




RoutineState
select_main_command()
{
    switch(get_routine_phase())
    {
  case(0):
      //need_to_refresh();

      change_current_object(&commandpillar);

      change_action_command(invalid_command);
      change_direct(Direct::none);
      change_routine_phase(1);
      break;
  case(1):
        if(get_direct() == Direct::advance)
        {
            switch(get_main_command())
            {
          case(MainCommand::move): push_routine(select_tag_from_destinations);       break;
          case(MainCommand::act ): push_routine(select_action_command);              break;
          case(MainCommand::use ): push_routine(select_tag_from_belongings);         break;
            }


          return RoutineState::finished;
        }
      break;
    }


  return RoutineState::working;
}


RoutineState
select_action_command()
{
    switch(get_routine_phase())
    {
  case(0):
      //need_to_refresh();

      change_current_object(&commandpillar);

        if(get_action_command() == invalid_command)
        {
          change_action_command(0);
        }


      change_direct(Direct::none);
      change_routine_phase(1);
      break;
  case(1):
        if(get_direct() == Direct::advance)
        {
          push_routine(select_tag_from_items);

          return RoutineState::finished;
        }

      else
        if(get_direct() == Direct::back)
        {
          push_routine(select_main_command);

          return RoutineState::finished;
        }
      break;
    }


  return RoutineState::working;
}


RoutineState
select_tag_from_destinations()
{
    switch(get_routine_phase())
    {
  case(0):
        if(!tagtable.refresh_by_destinations())
        {
          message.clear();

          message.push(u"いどうできる　ところは　ない");

          change_direct(Direct::none);

          push_routine(select_main_command);

          return RoutineState::finished;
        }

      else
        {
          //need_to_refresh();

          change_current_object(&tagtable);

          table_window.change_content(&tagtable);

          change_direct(Direct::none);
          change_routine_phase(1);
        }
      break;
  case(1):
        if(get_direct() == Direct::advance)
        {
          auto  plc = static_cast<Place*>(tagtable.get_tag());

            if(plc)
            {
              set_next_place(plc);

              push_routine(leave_place);
            }

          else
            {
              push_routine(select_main_command);
            }


          return RoutineState::finished;
        }

      else
        if(get_direct() == Direct::back)
        {
          push_routine(select_main_command);

          return RoutineState::finished;
        }
      break;
    }


  return RoutineState::working;
}




RoutineState
select_tag_from_items()
{
    switch(get_routine_phase())
    {
  case(0):
      //need_to_refresh();

      change_current_object(&tagtable);

      table_window.change_content(&tagtable);

      tagtable.refresh_by_items();

      change_direct(Direct::none);
      change_routine_phase(1);
      break;
  case(1):
        if(get_direct() == Direct::advance)
        {
          auto  item = static_cast<Item*>(tagtable.get_tag());

            if(!item)
            {
              change_direct(Direct::none);
            }

          else
            {
              message.clear();

                if(!item->react())
                {
                  push_routine(select_action_command);
                }


              return RoutineState::finished;
            }
        }

      else
        if(get_direct() == Direct::back)
        {
          push_routine(select_action_command);

          return RoutineState::finished;
        }
      break;
    }


  return RoutineState::working;
}




RoutineState
select_tag_from_belongings()
{
    switch(get_routine_phase())
    {
  case(0):
        if(!tagtable.refresh_by_belongings())
        {
          message.clear();

          message.push(u"なにも　もっていない！");

          change_direct(Direct::none);

          push_routine(select_main_command);

          return RoutineState::finished;
        }

      else
        {
          //need_to_refresh();

          change_current_object(&tagtable);

          table_window.change_content(&tagtable);

          change_direct(Direct::none);
          change_routine_phase(1);
        }
      break;
  case(1):
        if(get_direct() == Direct::advance)
        {
          push_routine(use_belongings);

          return RoutineState::finished;
        }

      else
        if(get_direct() == Direct::back)
        {
          push_routine(select_main_command);

          return RoutineState::finished;
        }
      break;
    }


  return RoutineState::working;
}




