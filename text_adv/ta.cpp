#include"ta.hpp"




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


Window  pillar_window(font::base_size* 8,font::base_size*14);
Window  table_window( font::base_size*26,font::base_size*12);


Container
container;




