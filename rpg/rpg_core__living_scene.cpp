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
        map.load("main.qbf");
        player.standby(map,Direction::left,Face::left,8,7);
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
      }
  }),



  Event("wardrobe",[](Square&  sq, Trigger  trig){

      switch(trig)
      {
    case(Trigger::press):
        message.push({
          u"ようふくダンスだ",
          u"ふくを　しまって　おけるぞ",
          u"でも　いまは　ひつようないな",
        });

        player.push_action({display_message});
        break;
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
          u"ちがいない",
        });

        player.push_action({display_message});
        break;
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




