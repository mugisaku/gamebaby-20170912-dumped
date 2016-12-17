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

  Event("change scene to main room",[](Square&  sq, Trigger  trig){
      switch(trig)
      {
    case(Trigger::begin_to_enter):
        break;
    case(Trigger::end_to_enter):
        map.load(load_file("data/main.qbf"));
        player.standby(map,Direction::left,Direction::left,8,7);
        change_scene(main_scene);
        break;
    case(Trigger::begin_to_leave):
        break;
    case(Trigger::end_to_leave):
        break;
    case(Trigger::press):
        break;
      }
  }),


  Event("bookshelf",[](Square&  sq, Trigger  trig){

      switch(trig)
      {
    case(Trigger::press):
        message.push({
          u"ほんだなだ",
          u"ほんを　こうりつてきに　しまっておける",
          u"とっても　べんりな　アイテムなのだ",
        });

        player.push_action({display_message});
        break;
    default:;
      }
  }),



  Event("wardrobe",[](Square&  sq, Trigger  trig){

      switch(trig)
      {
    case(Trigger::press):
        message.push({
          u"ようふくダンスだ",
          u"ふくを　しまって　おけるのだ",
        });

        player.push_action({display_message});
        break;
    default:;
      }
  }),



  Event("window",[](Square&  sq, Trigger  trig){

      switch(trig)
      {
    case(Trigger::press):
        message.push({
          u"まどだ",
          u"そとが　みえる",
          u"きっと　そとからも　こちらが　みえてるに",
          u"ちがいないのだ",
        });

        player.push_action({display_message});
        break;
    default:;
      }
  }),

};


}


const Scene
living_scene
{
  "",

  event_table,
};


}}}




