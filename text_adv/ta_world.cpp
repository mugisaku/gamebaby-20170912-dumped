#include"ta_world.hpp"
#include"ta.hpp"




namespace beginning_room{


constexpr uint32_t  unlocked__blue_door_flag = 2;
constexpr uint32_t     opened__red_door_flag = 4;
constexpr uint32_t    opened__blue_door_flag = 8;


extern Item   red_door;
extern Item  blue_door;


Item
red_door(u"あかい　とびら",[]()
{
    switch(get_action_command())
    {
  case(ActionCommand::look):
      message.push(u"あかい　とびらだ");

        if(!get_current_place()->get_flags().test(opened__red_door_flag))
        {
          message.push({u"いまは　しまっている"});
        }
      break;
  case(ActionCommand::take):
      message.push(u"とりはずせそうに　ない");
      break;
  case(ActionCommand::knock):
      message.push(u"こんこん・・・");

        if(!get_current_place()->get_flags().test(opened__red_door_flag))
        {
          message.push({u"へんじは　ない"});
        }
      break;
  case(ActionCommand::open):
        if(get_current_place()->get_flags().test(opened__red_door_flag))
        {
          message.push(u"すでに　あいている");
        }

      else
        {
          get_current_place()->get_flags().set(opened__red_door_flag);

          key_room::place.flags.unset(hiding_flag);

          message.push(u"とびらを　あけた");
        }
      break;
    }


  return 0;
});


Item
blue_door(u"あおい　とびら",[]()
{
    switch(get_action_command())
    {
  case(ActionCommand::look):
      message.push(u"あおい　とびらだ　かぎあなが　ある");

        if(!get_current_place()->get_flags().test(opened__blue_door_flag))
        {
          message.push({u"いまは　しまっている"});
        }
      break;
  case(ActionCommand::take):
      message.push(u"とりはずせそうに　ない");
      break;
  case(ActionCommand::knock):
      message.push(u"こんこん・・・");

        if(!get_current_place()->get_flags().test(opened__blue_door_flag))
        {
          message.push({u"へんじは　ない"});
        }
      break;
  case(ActionCommand::open):
        if(get_current_place()->get_flags().test(opened__blue_door_flag))
        {
          message.push(u"すでに　あいている");
        }

      else
        if(get_current_place()->get_flags().test(unlocked__blue_door_flag))
        {
          get_current_place()->get_flags().set(opened__blue_door_flag);

          uncharted_zone::place.flags.unset(hiding_flag);

          message.push(u"とびらを　あけた");
        }

      else
        {
          message.push(u"かぎが　かかっていて　あかない");
        }
      break;
    }


  return 0;
});




Place
place(u"はじまりのへや",[]()
{
    if(get_current_routine() == &visit_place)
    {
      message.push({u"ここは　はじまりの　へやだ",
                    u"あかい　とびらと",
                    u"あおい　とびらが　ある",
                    });
    }

  else
    if(get_current_routine() == &use_belongings)
    {
      auto  item = static_cast<Item*>(tagtable.get_tag());

        if(item)
        {
          const std::u16string  name(item->name);

            if(name == u"かぎ")
            {
              message.push({u"あおいとびらの　かぎあなに",
                            u"かぎを　さしこむと",
                            u"ぴたりと　はまった",
                            u"まわすと　かちゃりと　おとがした",
                            });


              erase_belongings(item);

              get_current_place()->get_flags().set(unlocked__blue_door_flag);

              return 1;
            }
        }
    }

  else
    if(get_current_routine() == &leave_place)
    {
    }


  return 0;
}
,{&key_room::place,&uncharted_zone::place},{&red_door,&blue_door});




}



namespace key_room{


constexpr uint32_t  appeared_key_flag = 2;
constexpr uint32_t       got_key_flag = 4;


extern       Item  wall;
extern HidingItem  key;


Item
wall(u"かべ",[]()
{
    switch(get_action_command())
    {
  case(ActionCommand::look):
      message.push(u"でこぼこした　かべだ");

        if(test_this_place_flags(appeared_key_flag))
        {
          message.push({u"いちぶは　くずれている"});
        }
      break;
  case(ActionCommand::take):
      message.push(u"かべを　とるって　どうやって？");
      break;
  case(ActionCommand::knock):
        if(test_this_place_flags(appeared_key_flag))
        {
          message.push({u"ごんっ",
                        u"かべを　ちからいっぱい　たたいてみると",
                        u"てが　いたくなった　だけだった",
                        });
        }

      else
        {
          message.push({u"ごんっ・・・ぽろ",
                        u"かべを　ちからいっぱい　たたいてみると",
                        u"かべの　いちぶが　くずれて",
                        u"なかから　かぎの　ようなものが　ころがり　でてきた",
                        });

          set_this_place_flags(appeared_key_flag);

          key.flags.unset(hiding_flag);
        }
      break;
  case(ActionCommand::open):
      message.push(u"あかない");
      break;
    }


  return 0;
});


HidingItem
key(u"かぎ",[]()
{
    switch(get_action_command())
    {
  case(ActionCommand::look):
      message.push(u"どこにでも　ありそうな　かぎだ");
      break;
  case(ActionCommand::take):
      message.push(u"かぎを　てにいれた");

      belongings_list.emplace_back(&key);

      set_this_place_flags(got_key_flag);

      key.get_flags().set(hiding_flag);
      break;
  case(ActionCommand::knock):
      message.push(u"こん");
      break;
  case(ActionCommand::open):
      message.push(u"あかない");
      break;
    }


  return 0;
});




HidingPlace
place(u"かぎの　へや",[]()
{
    if(get_current_routine() == &visit_place)
    {
      message.push({u"ここは　かぎの　へやだ"});
    }

  else
    if(get_current_routine() == &leave_place)
    {
    }


  return 0;
}
,{&beginning_room::place},{&wall,&key});




}



namespace uncharted_zone{


HidingPlace
place(u"みちの　りょういき",[]()
{
    if(get_current_routine() == &visit_place)
    {
       message.push({u"とびらの　さきには　さらなる　ぼうけんと　なぞが　まちかまえて　いた",
                     u"ふりそそぐ　しゃくねつの　おでん",
                     u"たちふさがる　しっこくの　でんしんばしら",
                     u"みだれとぶ　さつたば",
                     u"ひみつけっしゃ　くろまめだんの",
                     u"しんの　もくてきとは？",
                     u"ぼくの　たびは　はじまった　ばかりだ",
                     u"",
                     u"",
                     u"コマンドせんたくがた",
                     u"テキストアドベンチャー",
                     u"だい1ぶ　おしまい",
                     });
    }

  else
    if(get_current_routine() == &leave_place)
    {
    }


  return 0;
}
,{},{});




}




