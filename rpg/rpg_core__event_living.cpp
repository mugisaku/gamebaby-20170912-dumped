#include"rpg_core__private.hpp"




namespace gmbb{
namespace rpg{


namespace core{


const Event
living_event_table[] =
{
  Event("nop",[](Square&  sq, Trigger  trig){
    
  }),

  Event("change scene to main room",[](Square&  sq, Trigger  trig){
      switch(trig)
      {
    case(Trigger::begin_to_enter):
        break;
    case(Trigger::end_to_enter):
        map.load("main.qbf");
        player.standby(map,Direction::left,Face::left,8,7);
        change_current_event(main_event_table);
        break;
    case(Trigger::begin_to_leave):
        break;
    case(Trigger::end_to_leave):
        break;
    case(Trigger::press):
        break;
      }
  }),

};


}}}




