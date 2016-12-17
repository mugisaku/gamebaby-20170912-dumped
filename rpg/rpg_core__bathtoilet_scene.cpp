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

  ctx->get_sprite().height -= 12;

  ctx->change_interval_time(120);
 
  return 0;
}


Counter
submerge(Context&  ctx)
{
  ctx.counter.value += 1;

    if(ctx.counter < 12)
    {
      ctx->move_sprite_point(0,1);
      ctx->get_sprite().height  -= 1;
    }


    if(ctx.counter >= 24)
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
        map.load(load_file("data/main.qbf"));
        player.standby(map,Direction::front,Direction::front,8,7);
        change_scene(main_scene);
        break;
    case(Trigger::begin_to_leave):
        break;
    case(Trigger::end_to_leave):
        break;
    default:;
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
          move_to_back,
          move_to_back,
          move_to_back,
          move_to_back,
          move_to_back,
          move_to_back,
          move_to_back,
          move_to_back,
          move_to_back,
          move_to_back,
          rest,
          display_message,
          move_to_front,
          move_to_front,
          move_to_front,
          move_to_front,
          move_to_front,
          move_to_front,
          move_to_front,
          move_to_front,
          move_to_front,
          move_to_front,
          unset_quiet,
          unset_facefixed,
        });
        break;
    default:;
      }
  }),

  Event("bath",[](Square&  sq, Trigger  trig){
    Square*  base = &sq+2;

      switch(trig)
      {
    case(Trigger::press):
        player.push_action({
          turn_to_front,
          getin_to_bath,
          rest,
          submerge,
          rest,
          getout_from_bath,
        });
        break;
    default:;
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




