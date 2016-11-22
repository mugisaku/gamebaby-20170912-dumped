#include"game.hpp"
#include"game_routine.hpp"
#include"gmbb_controller.hpp"
#include"game_environment.hpp"




std::vector<Tag*>
belongings_list;


void
erase_belongings(const Item*  item)
{
    for(auto&  blng: belongings_list)
    {
        if(blng == item);
        {
          blng = nullptr;

          break;
        }
    }
}


CommandPillar
commandpillar;


TagTable
tagtable;


Message
message(22,5);


gmbb::Window  pillar_window(gmbb::font::base_size* 8,gmbb::font::base_size*14);
gmbb::Window  table_window( gmbb::font::base_size*26,gmbb::font::base_size*12);


gmbb::Container
container;




