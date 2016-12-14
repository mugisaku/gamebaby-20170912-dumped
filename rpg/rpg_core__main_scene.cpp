#include"rpg_core__private.hpp"




namespace gmbb{
namespace rpg{


namespace core{


namespace{


const Event
event_table[] =
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
        change_scene(living_scene);
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
        change_scene(bathtoilet_scene);
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


  Event("cooktop",[](Square&  sq, Trigger  trig){
      switch(trig)
      {
    case(Trigger::press):
        message.push({
          u"ガスコンロだ",
        });

        player.push_action({display_message});
        break;
      }
  }),


  Event("water supply",[](Square&  sq, Trigger  trig){
      switch(trig)
      {
    case(Trigger::press):
        message.push({
          u"すいどうだ",
        });

        player.push_action({display_message});
        break;
      }
  }),


  Event("washing machine",[](Square&  sq, Trigger  trig){
      switch(trig)
      {
    case(Trigger::press):
        message.push({
          u"せんたくきだ",
        });

        player.push_action({display_message});
        break;
      }
  }),


  Event("cardboard box",[](Square&  sq, Trigger  trig){
      switch(trig)
      {
    case(Trigger::press):
        message.push({
          u"だんボールばこだ",
        });

        player.push_action({display_message});
        break;
      }
  }),

};


}


const Scene
main_scene
{
  "",

  event_table,
};


}}}




