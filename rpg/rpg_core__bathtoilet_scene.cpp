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

  ctx->reset_sprite_point(24*7,24*6);

  ctx->change_shapeshift(bathtime_shapeshift);

  ctx->get_sprite().height -= 8;

  ctx->change_interval_time(120);
 
  return 0;
}


Counter
submerge(Context&  ctx)
{
  ctx.counter.value += 1;

    if(ctx.counter < 16)
    {
      ctx->move_sprite_point(0,1);
      ctx->get_sprite().height  -= 1;
    }


    if(ctx.counter >= 32)
    {
      ctx.counter.value = 0;
    }


  return ctx.counter;
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

  ctx->reset_sprite_point(24*3,24*7);

  ctx->change_shapeshift(basic_shapeshift);

  ctx->change_interval_time(40);

  return 0;
}




const Event
event_table[] =
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
        change_scene(main_scene);
        break;
    case(Trigger::begin_to_leave):
        break;
    case(Trigger::end_to_leave):
        break;
      }
  }),

  Event("toilet",[](Square&  sq, Trigger  trig){
      switch(trig)
      {
    case(Trigger::press):
        message.push({u"ふー"});

        player.push_action({
          turn_to_front,
          set_quiet,
          set_facefixed,
          move_up,
          display_message,
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
        player.push_action({
          turn_to_front,
          getin_to_bath,
          rest,
          submerge,
          rest,
          getout_from_bath,
        });
        break;
      }
  }),

};


}


const Scene
bathtoilet_scene
{
  "",

  event_table,
};


}}}




