#include"rpg_core__private.hpp"




namespace gmbb{
namespace rpg{


namespace core{


const Event
main_event_table[] =
{
  Event("nop",[](Square&  sq, Trigger  trig){
    
  }),

  Event("change scene to living room",[](Square&  sq, Trigger  trig){
      switch(trig)
      {
    case(Trigger::begin_to_enter):
        break;
    case(Trigger::end_to_enter):
        map.load("living.qbf");
        player.standby(map,Direction::right,Face::right,4,7);
        change_current_event(living_event_table);
        break;
    case(Trigger::begin_to_leave):
        break;
    case(Trigger::end_to_leave):
        break;
    case(Trigger::press):
        break;
      }
  }),

  Event("door to bathtoilet room",[](Square&  sq, Trigger  trig){
      switch(trig)
      {
    case(Trigger::begin_to_enter):
        break;
    case(Trigger::end_to_enter):
        map.load("bathtoilet.qbf");
        player.standby(map,Direction::up,Face::back,3,8);
        change_current_event(bathtoilet_event_table);
        break;
    case(Trigger::begin_to_leave):
        break;
    case(Trigger::end_to_leave):
        break;
    case(Trigger::press):
          if(set_flag(Section::temporary,1))
          {
            sq.attribute &= ~noentry_flag;
            sq.lower.x += 4;
            ((&sq)-map.get_width())->lower.x += 4;
          }
        break;
      }
  }),

};


}}}




