#include"game_commandpillar.hpp"
#include"gmbb.hpp"
#include"cbes_screen.hpp"




namespace{
int  action_command;
int  main_command;
}


int    get_main_command(){return   main_command;}
int  get_action_command(){return action_command;}


void  change_main_command(int  v){main_command = v;}
void  change_action_command(int  v){action_command = v;}




void
CommandPillar::
process(Controller&  ctrl)
{
    if(action_command != invalid_command)
    {
        if(ctrl.test_pressed(keyflag::up) && action_command)
        {
          action_command -= 1;

          cbes::screen.need_to_refresh();
        }

      else
        if(ctrl.test_pressed(keyflag::down) && (action_command < ActionCommand::LAST))
        {
          action_command += 1;

          cbes::screen.need_to_refresh();
        }

      else
        if(ctrl.test_pressed(keyflag::p))
        {
          change_direct(Direct::advance);
        }

      else
        if(ctrl.test_pressed(keyflag::n))
        {
          change_direct(Direct::back);
        }
    }

  else
    {
        if(ctrl.test_pressed(keyflag::up) && main_command)
        {
          main_command -= 1;

          cbes::screen.need_to_refresh();
        }

      else
        if(ctrl.test_pressed(keyflag::down) && (main_command < MainCommand::LAST))
        {
          main_command += 1;

          cbes::screen.need_to_refresh();
        }

      else
        if(ctrl.test_pressed(keyflag::p))
        {
          change_direct(Direct::advance);
        }
    }
}


void
CommandPillar::
render(cbes::CharacterTable&  dst)
{
  int  x = point.x;
  int  y = point.y;

    if(action_command != invalid_command)
    {
        if(get_current_object() == this)
        {
          dst.printf_tall(x,y+(2*action_command),"○");
        }


        dst.printf_tall(x+1,y,"みる");  y += 2;
        dst.printf_tall(x+1,y,"とる");  y += 2;
        dst.printf_tall(x+1,y,"たたく");  y += 2;
        dst.printf_tall(x+1,y,"あける");
    }

  else
    {
        if(get_current_object() == this)
        {
          dst.printf_tall(x,y+(2*main_command),"○");
        }


        dst.printf_tall(x+1,y,"いどう");  y += 2;
        dst.printf_tall(x+1,y,"こうどう");  y += 2;
        dst.printf_tall(x+1,y,"もちもの");
    }
}





