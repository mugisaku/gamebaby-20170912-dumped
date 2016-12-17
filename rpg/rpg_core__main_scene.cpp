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
        map.load(load_file("data/living.qbf"));
        player.standby(map,Direction::right,Direction::right,4,7);
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
        map.load(load_file("data/bathtoilet.qbf"));
        player.standby(map,Direction::back,Direction::back,3,8);
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
    default:;
      }
  }),


  Event("cooktop",[](Square&  sq, Trigger  trig){
      switch(trig)
      {
    case(Trigger::press):
        message.push({
          u"ガスコンロだ",
          u"にるなり　やくなり　すきにできるのだ",
        });

        player.push_action({display_message});
        break;
    default:;
      }
  }),


  Event("water supply",[](Square&  sq, Trigger  trig){
      switch(trig)
      {
    case(Trigger::press):
        message.push({
          u"すいどうだ",
          u"みずを　のんだり　てを　あらったりと",
          u"だいかつやく　なのだ",
        });

        player.push_action({display_message});
        break;
    default:;
      }
  }),


  Event("washing machine",[](Square&  sq, Trigger  trig){
      switch(trig)
      {
    case(Trigger::press):
        message.push({
          u"せんたくきだ",
          u"あらう　すすぐ　だっすいの　れんぞくこうげきに",
          u"いふくの　よごれは　ひとたまりも　ないのだ",
        });

        player.push_action({display_message});
        break;
    default:;
      }
  }),


  Event("cardboard box",[](Square&  sq, Trigger  trig){
      switch(trig)
      {
    case(Trigger::press):
        message.push({
          u"だんボールばこだ",
          u"ものを　はこぶには　かかせないのだ",
        });

        player.push_action({display_message});
        break;
    default:;
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




