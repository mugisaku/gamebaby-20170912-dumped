#include"ta_commandpillar.hpp"
#include"ta.hpp"




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
        if(ctrl.test_pressed(up_flag) && action_command)
        {
          action_command -= 1;

          need_to_refresh();
        }

      else
        if(ctrl.test_pressed(down_flag) && (action_command < ActionCommand::LAST))
        {
          action_command += 1;

          need_to_refresh();
        }

      else
        if(ctrl.test_pressed(p_flag))
        {
          change_direct(Direct::advance);
        }

      else
        if(ctrl.test_pressed(n_flag))
        {
          change_direct(Direct::back);
        }
    }

  else
    {
        if(ctrl.test_pressed(up_flag) && main_command)
        {
          main_command -= 1;

          need_to_refresh();
        }

      else
        if(ctrl.test_pressed(down_flag) && (main_command < MainCommand::LAST))
        {
          main_command += 1;

          need_to_refresh();
        }

      else
        if(ctrl.test_pressed(p_flag))
        {
          change_direct(Direct::advance);
        }
    }
}


void
CommandPillar::
render(Image&  dst)
{
  gmbb::PrintPoint  x(point.x);
  gmbb::PrintPoint  y(point.y);

    if(action_command != invalid_command)
    {
        if(get_current_object() == this)
        {
          dst.print_tall("○",gmbb::font_color,x,y+(2*action_command));
        }


        dst.print_tall("みる",gmbb::font_color,x+1,y);  y += 2;
        dst.print_tall("とる",gmbb::font_color,x+1,y);  y += 2;
        dst.print_tall("たたく",gmbb::font_color,x+1,y);  y += 2;
        dst.print_tall("あける",gmbb::font_color,x+1,y);
    }

  else
    {
        if(get_current_object() == this)
        {
          dst.print_tall("○",gmbb::font_color,x,y+(2*main_command));
        }


        dst.print_tall("いどう",gmbb::font_color,x+1,y);  y += 2;
        dst.print_tall("こうどう",gmbb::font_color,x+1,y);  y += 2;
        dst.print_tall("もちもの",gmbb::font_color,x+1,y);
    }
}





