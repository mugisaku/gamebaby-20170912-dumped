#include"rpg_core__private.hpp"




namespace gmbb{
namespace rpg{


namespace core{


namespace{


Counter
getin_to_bath(Context&  ctx)
{
  map.get(6,5).lower.x += 3;
  map.get(7,5).lower.x += 3;
  map.get(6,6).lower.x += 3;
  map.get(7,6).lower.x += 3;
  map.get(6,7).lower.x += 3;
  map.get(7,7).lower.x += 3;

  return 0;
}


Counter
submerge(Context&  ctx)
{
rest(ctx);

  return 0;
}


Counter
getout_from_bath(Context&  ctx)
{
  map.get(6,5).lower.x -= 3;
  map.get(7,5).lower.x -= 3;
  map.get(6,6).lower.x -= 3;
  map.get(7,6).lower.x -= 3;
  map.get(6,7).lower.x -= 3;
  map.get(7,7).lower.x -= 3;

  return 0;
}




}


const Event
bathtoilet_event_table[] =
{
  Event("nop",[](Square&  sq, Trigger  trig){
    
  }),

  Event("to main room",[](Square&  sq, Trigger  trig){
      switch(trig)
      {
    case(Trigger::begin_to_enter):
        break;
    case(Trigger::end_to_enter):
        map.load("main.qbf");
        player.standby(map,Direction::down,Face::front,8,7);
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

  Event("toilet",[](Square&  sq, Trigger  trig){
      switch(trig)
      {
    case(Trigger::begin_to_enter):
        break;
    case(Trigger::end_to_enter):
        break;
    case(Trigger::begin_to_leave):
        break;
    case(Trigger::end_to_leave):
        break;
    case(Trigger::press):
        player.push_action({
          turn_to_front,
          set_quiet,
          set_facefixed,
          move_up,
          rest,
          move_down,
          unset_quiet,
          unset_facefixed,
        });
        break;
      }
  }),

  Event("bath",[](Square&  sq, Trigger  trig){
    Square*  base = &sq+2;

      switch(trig)
      {
    case(Trigger::begin_to_enter):
        break;
    case(Trigger::end_to_enter):
        break;
    case(Trigger::begin_to_leave):
        break;
    case(Trigger::end_to_leave):
        break;
    case(Trigger::press):
        player.push_action({
          turn_to_front,
          getin_to_bath,
          submerge,
          getout_from_bath,
        });
        break;
      }
  }),

};


}}}




